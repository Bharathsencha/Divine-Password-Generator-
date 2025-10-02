# Divine Password Generator

A secure password generator with a GUI interface built using raylib. Generate strong, random passwords between 12 and 999 characters with proper cryptographic randomness.

## What This Does

This program generates truly random passwords using your operating system's built-in random number generator. Unlike simple random functions that can be predicted, this uses the same cryptographic sources that secure websites and encryption software rely on.

The GUI lets you type in how long you want your password, click generate, and copy it to your clipboard. Simple as that.

## How It Works

### Getting Random Numbers

The core of password generation is `std::random_device`. This isn't just a regular random number generator. On Linux, it reads from `/dev/urandom`, which collects entropy from system events like keyboard timings, mouse movements, and hardware interrupts. On Windows, it uses `CryptGenRandom`, Microsoft's cryptographic API.

When you click generate, the program asks the OS for random bytes, and the OS gives back numbers that are genuinely unpredictable.

### Avoiding Bias

Here's a problem most people don't think about: if you want a random number between 0 and 10, you might think to do `random() % 10`. But this creates bias. If your random function gives numbers 0-15, then 0-5 appear more often than 6-9.

We fix this with rejection sampling:

```cpp
size_t range = UINT32_MAX - (UINT32_MAX % max);
size_t value;
do {
    value = rd();
} while (value >= range);
return value % max;
```

Basically, if we get a number in the "biased zone", we throw it away and ask for a new one. Keep doing this until we get a number in the fair range. This guarantees every character has exactly the same chance of being picked.

### Building the Password

The generator doesn't just grab random characters. Here's the step-by-step:

1. **Set up character pools**: We have four groups - numbers (0-9), lowercase letters (a-z), uppercase letters (A-Z), and symbols (!@#$ etc.)

2. **Guarantee diversity**: Calculate how many characters we need from each group. For a 16-character password, we need at least 2 from each category. For longer passwords, we scale this up.

3. **Fill the minimum**: Add the required number of characters from each group to guarantee the password isn't all lowercase or all numbers.

4. **Fill the rest**: For remaining spots, pick randomly from all characters mixed together.

5. **Shuffle everything**: This is important. Without shuffling, all your numbers would be at the start, then uppercase, then lowercase, etc. Predictable pattern.

### The Shuffle Algorithm

We use Fisher-Yates shuffle. It works like shuffling a deck of cards:

```cpp
for (size_t i = password.length() - 1; i > 0; i--) {
    size_t j = secRand.getInRange(i + 1);
    std::swap(password[i], password[j]);
}
```

Start at the end of the password. Pick a random position before it and swap them. Move one position back. Repeat. This guarantees every possible arrangement of characters has equal probability.

### Why Minimum 12 Characters?

Shorter passwords are easier to crack through brute force. Modern computers can try billions of passwords per second. A 12-character password with mixed characters has enough combinations that even the fastest computers would take years to crack it.

### Code Organization

**main.cpp**: Just calls the GUI function. That's it.

**generator.cpp**: Contains all the password generation logic. The `SecureRandom` class handles getting random bytes from the OS and converting them to usable numbers. The `generatePassword()` function ties everything together.

**gui.cpp**: Handles the raylib window, input boxes, buttons, and display. Updates 60 times per second to handle mouse clicks and keyboard input.

## Building and Running

### Prerequisites

You need raylib installed on your system.

**On Linux (Ubuntu/Debian):**
```bash
sudo apt-get install libraylib-dev
```

**On Windows:**
Install MinGW or MSYS2, then install raylib through your package manager or download from the official website.

### Compilation

The Makefile automatically detects your operating system and uses the correct settings. Just run:

```bash
make
```

This compiles all source files and links them with raylib.

### Other Make Commands

```bash
make clean    # Remove compiled files
make rebuild  # Clean and build from scratch
make run      # Build and run the program
make help     # Show available commands
```

### Manual Compilation

If you want to compile manually:

**Linux:**
```bash
gcc -std=c11 main.c gui.c generator.c -o password_gen -lraylib -lm -lpthread -ldl -lrt -lX11
```

**Windows:**
```bash
gcc -std=c11 main.c gui.c generator.c -o password_gen.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

## Using the Program

1. Run the executable (`./password_gen` on Linux or `password_gen.exe` on Windows)
2. Click on the input box
3. Clear the default number and type your desired password length (12-999)
4. Click the GENERATE button
5. Your password appears in the gray box
6. Click COPY to copy it to your clipboard

The password won't be visible anywhere else, so make sure to paste it where you need it before closing the program.

## Technical Notes

### Why Not Use Simple rand()?

The old C `rand()` function is predictable. If someone knows when you generated your password, they can reproduce the same sequence. It's also platform-dependent and has a small internal state, making it unsuitable for security.

### Memory Safety

Passwords are stored in C++ strings, which are automatically managed. When the program closes, the memory is freed. However, the password remains in your clipboard until you copy something else.

### Character Set

The special symbols include: `!@#$%^&*()_+-=[]{}|;:,.<>?/~` and more. Some systems might have issues with certain symbols, but most modern systems and websites accept all of these.

