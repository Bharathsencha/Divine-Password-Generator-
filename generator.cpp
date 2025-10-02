#include "generator.h"
#include <algorithm>
#include <random>
#include <fstream>

// Cryptographically secure random number generation
class SecureRandom {
private:
    std::random_device rd;
    
public:
    // Get cryptographically secure random bytes
    void getBytes(unsigned char* buffer, size_t length) {
        for (size_t i = 0; i < length; i++) {
            buffer[i] = static_cast<unsigned char>(rd());
        }
    }
    
    // Get a random number in range [0, max)
    size_t getInRange(size_t max) {
        if (max == 0) return 0;
        
        // Use rejection sampling to avoid modulo bias
        size_t range = UINT32_MAX - (UINT32_MAX % max);
        size_t value;
        
        do {
            value = rd();
        } while (value >= range);
        
        return value % max;
    }
};

std::string generatePassword(int length) {
    // Enforce minimum length of 12 for security
    if (length < 12) length = 12;
    if (length > 9999) length = 9999;
    
    // Character sets for strong passwords
    const std::string numbers = "0123456789";
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string symbols = "!@#$%^&*()_+-=[]{}|;:,.<>?/~`'\"\\";
    
    // Combine all character sets
    std::string allChars = numbers + lowercase + uppercase + symbols;
    
    SecureRandom secRand;
    std::string password;
    password.reserve(length);
    
    // Calculate minimum characters per category for strong passwords
    // Ensure good distribution across all character types
    int minPerCategory = std::max(2, length / 8);
    
    // Add minimum required characters from each category
    for (int i = 0; i < minPerCategory; i++) {
        password += numbers[secRand.getInRange(numbers.length())];
        password += lowercase[secRand.getInRange(lowercase.length())];
        password += uppercase[secRand.getInRange(uppercase.length())];
        password += symbols[secRand.getInRange(symbols.length())];
    }
    
    // Fill remaining length with random characters from all sets
    while (password.length() < static_cast<size_t>(length)) {
        password += allChars[secRand.getInRange(allChars.length())];
    }
    
    // Cryptographically secure shuffle using Fisher-Yates algorithm
    // with secure random source
    for (size_t i = password.length() - 1; i > 0; i--) {
        size_t j = secRand.getInRange(i + 1);
        std::swap(password[i], password[j]);
    }
    
    return password;
}