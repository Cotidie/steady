FROM osrf/ros:jazzy-desktop

# Avoid interactive prompts during apt operations
ARG DEBIAN_FRONTEND=noninteractive

# Copy the install script in and run it
COPY install-zsh.sh /tmp/install-zsh.sh
RUN chmod +x /tmp/install-zsh.sh && /tmp/install-zsh.sh && rm /tmp/install-zsh.sh

WORKDIR /app

# Set zsh as the default shell for interactive sessions
SHELL ["/bin/zsh", "-c"]
CMD ["/bin/zsh"]
