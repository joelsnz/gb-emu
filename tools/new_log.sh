#!/bin/bash

DEVLOG_DIR="devlog"
DATE=$(date +"%Y-%m-%d")
EDITOR="nvim"

FILE="$DEVLOG_DIR/$DATE.md"

if [ -f "$FILE" ]; then
    echo "Devlog ($FILE) exists."
    exit 1
fi

cat <<EOL > "$FILE"
# Devlog $DATE
## Changes
-
## To-Do
-
EOL

$EDITOR $FILE
