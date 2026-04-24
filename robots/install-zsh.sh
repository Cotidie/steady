#!/bin/bash

# Stop script on errors (optional, but good for debugging)
set -e

install_dependencies() {
    echo "--- Step 0: Installing Tools & Git Config ---"
    apt update
    apt install -y vim git fonts-font-awesome curl wget

    # Configure Git
    git config --global core.editor "vim"
    git config --global user.name "$GIT_NAME"
    git config --global user.email "$GIT_EMAIL"

    echo "Git configured for $GIT_NAME <$GIT_EMAIL>"
}

install_zsh() {
    echo "--- Step 1: Installing Zsh ---"
   apt install -y zsh
    echo "Changing default shell to zsh..."
    chsh -s $(which zsh)
}

install_oh_my_zsh() {
    echo "--- Step 2: Installing Oh My Zsh and Plugins ---"

    if [ ! -d "$HOME/.oh-my-zsh" ]; then
        sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended
    else
        echo "Oh My Zsh is already installed. Skipping..."
    fi
    
    ZSH_CUSTOM=${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}

    echo "Cloning plugins..."
    if [ ! -d "$ZSH_CUSTOM/plugins/zsh-autosuggestions" ]; then
        git clone https://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions
    fi

    if [ ! -d "$ZSH_CUSTOM/plugins/zsh-syntax-highlighting" ]; then
        git clone https://github.com/zsh-users/zsh-syntax-highlighting.git $ZSH_CUSTOM/plugins/zsh-syntax-highlighting
    fi
}

configure_zshrc() {
    echo "--- Step 3: Configuring .zshrc ---"
    local ZSHRC_FILE="$HOME/.zshrc"

    # 1. Update the plugins list using sed
    sed -i 's/^plugins=(git)/plugins=(\n    git\n    docker\n    docker-compose\n    zsh-autosuggestions\n    zsh-syntax-highlighting\n)/' "$ZSHRC_FILE"

    # 2. Add keybindings to the end of the file
    if ! grep -q "history-beginning-search-backward" "$ZSHRC_FILE"; then
        cat <<EOT >> "$ZSHRC_FILE"

# Custom Keybindings
bindkey "^[[A" history-beginning-search-backward    # Up Arrow (Previous command matching)
bindkey "^[[B" history-beginning-search-forward     # Down Arrow (Next command matching)
EOT
    fi
}

main() {
    echo "Starting setup..."
    
    install_dependencies
    install_zsh
    install_oh_my_zsh
    configure_zshrc

    echo "--- Setup Complete! ---"
    echo "Please restart your terminal or log out and log back in to see changes."
    echo "If you are already in zsh, run: source ~/.zshrc"
}

main 
