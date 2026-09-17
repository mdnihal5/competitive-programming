#!/usr/bin/env bash
#
# One-shot setup for this repo's competitive-programming Vim environment.
#
#   bash -c "$(curl -fsSL https://raw.githubusercontent.com/mdnihal5/competitive-programming/main/install.sh)"
#
# What it does, in order:
#   1. Clones (or updates) this repo to ~/Personal/competitive-programming --
#      that exact path is load-bearing: cpp.snippets' python interpolations
#      resolve debug.hpp / INDEX.md against it (see Readme.md).
#   2. Installs g++, astyle, a Vim built with +python3, and a clipboard tool,
#      via apt on Linux / Homebrew on macOS. Skips anything already present.
#   3. Bootstraps vim-plug if it isn't already installed.
#   4. Symlinks (not copies) ~/.vimrc and ~/.vim/UltiSnips at the repo's
#      copies, so the live config and the repo can never drift apart again --
#      that drift is exactly what broke the `list` snippet once already.
#      Anything already at those paths is backed up first, never overwritten.
#   5. Wires vimrc/bash_aliases into ~/.bashrc / ~/.zshrc (idempotent).
#   6. Runs :PlugInstall headless once.
#
# Re-running is safe -- every step checks before it acts.
#
# CP_SETUP_DRY_RUN=1 prints what it would do without installing packages,
# touching dotfiles, or running vim. Used to verify this script; also a
# legitimate way to preview it before trusting a curl-pipe-bash script.

set -euo pipefail

DRY_RUN="${CP_SETUP_DRY_RUN:-0}"
REPO_URL="https://github.com/mdnihal5/competitive-programming.git"
TARGET_DIR="$HOME/Personal/competitive-programming"

c_bold=$'\033[1m'; c_grn=$'\033[32m'; c_yel=$'\033[33m'; c_red=$'\033[31m'; c_rst=$'\033[0m'
log()  { printf '%s\n' "${c_bold}==>${c_rst} $*"; }
ok()   { printf '%s\n' "${c_grn}  ok${c_rst}  $*"; }
skip() { printf '%s\n' "${c_yel}skip${c_rst}  $*"; }
warn() { printf '%s\n' "${c_red}warn${c_rst}  $*" >&2; }
run()  {
  if [ "$DRY_RUN" = "1" ]; then
    printf '%s\n' "${c_yel}dry-run${c_rst} $*"
  else
    "$@"
  fi
}

need_sudo() {
  if [ "$(id -u)" -eq 0 ]; then return 1; fi
  command -v sudo >/dev/null 2>&1
}

OS="$(uname -s)"

#-------------------------------------------------------------------------
# 1. Clone / update the repo at the exact path the snippets expect.
#-------------------------------------------------------------------------
log "Repo -> $TARGET_DIR"
if [ -d "$TARGET_DIR/.git" ]; then
  ok "already cloned"
  run git -C "$TARGET_DIR" pull --ff-only
else
  run mkdir -p "$(dirname "$TARGET_DIR")"
  run git clone "$REPO_URL" "$TARGET_DIR"
fi

#-------------------------------------------------------------------------
# 2. OS packages.
#-------------------------------------------------------------------------
install_linux_packages() {
  log "Linux packages (g++, astyle, vim with +python3, clipboard)"
  if ! command -v apt-get >/dev/null 2>&1; then
    warn "no apt-get found -- install g++, astyle, a +python3 Vim, and xclip/wl-clipboard yourself, then re-run"
    return
  fi
  local sudo_cmd=""
  need_sudo && sudo_cmd="sudo"

  local to_install=()
  command -v g++ >/dev/null 2>&1 || to_install+=(g++)
  command -v astyle >/dev/null 2>&1 || to_install+=(astyle)
  # Ubuntu's plain `vim`/`vim-tiny` package usually lacks +python3, which
  # UltiSnips' `!p` blocks need -- vim-nox is the headless build that has it.
  if command -v vim >/dev/null 2>&1 && vim --version 2>/dev/null | grep -q '+python3'; then
    :
  else
    to_install+=(vim-nox)
  fi
  if [ -n "${WAYLAND_DISPLAY:-}" ]; then
    command -v wl-copy >/dev/null 2>&1 || to_install+=(wl-clipboard)
  else
    command -v xclip >/dev/null 2>&1 || to_install+=(xclip)
  fi
  command -v git >/dev/null 2>&1 || to_install+=(git)
  command -v curl >/dev/null 2>&1 || to_install+=(curl)

  if [ "${#to_install[@]}" -eq 0 ]; then
    ok "everything already present"
    return
  fi
  log "installing: ${to_install[*]}"
  run $sudo_cmd apt-get update -qq
  run $sudo_cmd apt-get install -y "${to_install[@]}"
}

install_macos_packages() {
  log "macOS packages (gcc, astyle, vim with +python3)"
  if ! command -v brew >/dev/null 2>&1; then
    warn "Homebrew not found. This script won't bootstrap it for you --"
    warn "install it from https://brew.sh, then re-run this script."
    return 1
  fi
  # macOS's own g++ is Apple Clang wearing a g++ name -- no bits/stdc++.h,
  # no PBDS. Real GNU g++ comes from `brew install gcc` (see Readme.md).
  local to_install=()
  ls /opt/homebrew/bin/g++-* /usr/local/bin/g++-* >/dev/null 2>&1 || to_install+=(gcc)
  command -v astyle >/dev/null 2>&1 || to_install+=(astyle)
  # macOS ships an old vim without +python3; brew's does.
  if command -v vim >/dev/null 2>&1 && vim --version 2>/dev/null | grep -q '+python3'; then
    :
  else
    to_install+=(vim)
  fi

  if [ "${#to_install[@]}" -eq 0 ]; then
    ok "everything already present"
    return
  fi
  log "brew installing: ${to_install[*]}"
  run brew install "${to_install[@]}"
}

case "$OS" in
  Linux)  install_linux_packages ;;
  Darwin) install_macos_packages ;;
  *) warn "unrecognized OS '$OS' -- install g++, astyle and a +python3 Vim yourself, then re-run" ;;
esac

#-------------------------------------------------------------------------
# 3. vim-plug.
#-------------------------------------------------------------------------
PLUG_VIM="$HOME/.vim/autoload/plug.vim"
log "vim-plug"
if [ -f "$PLUG_VIM" ]; then
  ok "already installed"
else
  run mkdir -p "$(dirname "$PLUG_VIM")"
  run curl -fsSLo "$PLUG_VIM" \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
fi

#-------------------------------------------------------------------------
# 4. Symlink vimrc + UltiSnips. Back up anything real that's already there.
#-------------------------------------------------------------------------
backup_and_link() {
  local src="$1" dst="$2"
  if [ -L "$dst" ] && [ "$(readlink "$dst")" = "$src" ]; then
    ok "$dst already symlinked correctly"
    return
  fi
  if [ -e "$dst" ] || [ -L "$dst" ]; then
    local bak="${dst}.pre-cp-setup.bak"
    log "backing up existing $dst -> $bak"
    run mv "$dst" "$bak"
  fi
  run mkdir -p "$(dirname "$dst")"
  run ln -sfn "$src" "$dst"
  ok "linked $dst -> $src"
}

log "Symlinking vimrc + UltiSnips"
backup_and_link "$TARGET_DIR/vimrc/vimrc" "$HOME/.vimrc"
backup_and_link "$TARGET_DIR/vimrc/UltiSnips" "$HOME/.vim/UltiSnips"

#-------------------------------------------------------------------------
# 5. bash_aliases: never overwrite the user's own file. Symlink the repo's
#    copy under its own name and source it, idempotently, from shell rc
#    files that exist.
#-------------------------------------------------------------------------
log "Wiring bash_aliases (cstart)"
CP_ALIASES_LINK="$HOME/.cp_bash_aliases"
backup_and_link "$TARGET_DIR/vimrc/bash_aliases" "$CP_ALIASES_LINK"

SOURCE_LINE="[ -f \"$CP_ALIASES_LINK\" ] && source \"$CP_ALIASES_LINK\"  # competitive-programming: cstart"
for rc in "$HOME/.bashrc" "$HOME/.zshrc"; do
  [ -f "$rc" ] || continue
  if grep -qF "$CP_ALIASES_LINK" "$rc" 2>/dev/null; then
    ok "$rc already sources it"
  else
    log "appending source line to $rc"
    if [ "$DRY_RUN" = "1" ]; then
      printf '%s\n' "${c_yel}dry-run${c_rst} append to $rc: $SOURCE_LINE"
    else
      printf '\n%s\n' "$SOURCE_LINE" >> "$rc"
    fi
  fi
done

#-------------------------------------------------------------------------
# 6. Fetch the plugins (onedark.vim, UltiSnips) headless.
#-------------------------------------------------------------------------
log "Installing Vim plugins"
if [ "$DRY_RUN" = "1" ]; then
  printf '%s\n' "${c_yel}dry-run${c_rst} vim -u \"$HOME/.vimrc\" +PlugInstall! +qall"
else
  vim -u "$HOME/.vimrc" +PlugInstall! +qall || warn "PlugInstall reported an issue -- open vim and run :PlugStatus"
fi

#-------------------------------------------------------------------------
# Done.
#-------------------------------------------------------------------------
cat <<EOF

${c_grn}${c_bold}Set up.${c_rst}

  \$ cstart abcd a,b,c        # new contest, opens a.cpp
  (in vim, insert mode)  normal<Tab>       -- base template
                          DSU<Tab>         -- any trigger from vimrc/UltiSnips/INDEX.md
                          list<Tab>        -- print every trigger + description
                          segt<C-x><C-u>   -- search triggers by substring, <CR> then <Tab>

No ~/.astylerc is shipped -- Format() (<C-b>, <Space>f) looks for one and
falls back to astyle's defaults if it's missing. Write your own at
~/.astylerc if you want a specific brace style.
EOF
