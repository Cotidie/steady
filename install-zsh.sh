#!/bin/bash

# Stop script on errors (optional, but good for debugging)
set -e

echo "Starting setup..."

# --- Step 0: Install useful tools & Configure Git ---
echo "--- Step 0: Installing Tools & Git Config ---"
sudo apt update
sudo apt install -y vim git fonts-font-awesome curl wget

# Request User Input
echo ""
read -p "Enter your Git User Name (NickName): " GIT_NAME
read -p "Enter your Git Email Address: " GIT_EMAIL

# Configure Git
git config --global core.editor "vim"
git config --global user.name "$GIT_NAME"
git config --global user.email "$GIT_EMAIL"

echo "Git configured for $GIT_NAME <$GIT_EMAIL>"


# --- Step 1: Install Zsh ---
echo "--- Step 1: Installing Zsh ---"
sudo apt install -y zsh
echo "Changing default shell to zsh..."
chsh -s $(which zsh)

# --- Step 2: Install Oh My Zsh & Plugins ---
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


# --- Step 3: Configure .zshrc ---
echo "--- Step 3: Configuring .zshrc ---"
ZSHRC_FILE="$HOME/.zshrc"

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

echo "--- Setup Complete! ---"
echo "Please restart your terminal or log out and log back in to see changes."
echo "If you are already in zsh, run: source ~/.zshrc" 
