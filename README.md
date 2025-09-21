```bash
# Install boost
brew install boost
pacman -S boost

# Compile with boost
g++ file.cpp -o file.out -I/opt/homebrew/include -L/opt/homebrew/lib -lboost_program_options

# Run
./file.out -o count -f shapes.txt
```
