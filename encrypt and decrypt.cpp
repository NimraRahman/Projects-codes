#include <botan/aes.h>
#include <botan/bcrypt.h>
#include <botan/ccm.h>
#include <botan/filters.h>
#include <botan/hex.h>
#include <botan/rng.h>
#include <iostream>

using namespace Botan;
using namespace std;

string hash_password(const string& password)
{
    const size_t salt_size = 16; // use a 128-bit salt
    System_RNG rng;
    string salt = rng.random_vec(salt_size);
    const size_t work_factor = 12; // adjust this as needed
    return generate_bcrypt(password, rng, work_factor, salt);
}

SymmetricKey derive_key(const string& password)
{
    const size_t output_size = 16; // use a 128-bit key for AES-CCM
    const string hash = hash_password(password);
    const size_t salt_size = 16; // retrieve the salt used in the hash
    const string salt = hash.substr(0, salt_size);
    System_RNG rng;
    return PBKDF2_HMAC<SHA_256>(password, salt, 10000, output_size, rng);
}

string encrypt(const string& message, const string& password, RandomNumberGenerator& rng)
{
    // derive the key using the password
    const SymmetricKey key = derive_key(password);

    // set up AES-CCM cipher
    InitializationVector iv(rng, 8); // use an 8-byte IV for AES-CCM
    CCM_Encryption ccm(key, iv, 8, 13); // specify the tag length and nonce length

    // encrypt message using AES-CCM
    string ciphertext = ccm.start(message.size());
    StringSource(message, true, new AuthenticatedEncryptionFilter(ccm, new StringSink(ciphertext)));

    // construct the encrypted message
    string encrypted;
    encrypted += hex_encode(iv.bits_of());
    encrypted += hex_encode(ccm.get_tag().bits_of());
    encrypted += hex_encode(key.bits_of());
    encrypted += ciphertext;
    return encrypted;
}

string decrypt(const string& encrypted, const string& password, RandomNumberGenerator& rng)
{
    // extract the IV, tag, key, and ciphertext from the encrypted message
    if (encrypted.length() < 64) {
        throw runtime_error("Error: Invalid encrypted message!");
    }

    InitializationVector iv(hex_decode(encrypted.substr(0, 16)));
    SecureVector<byte> tag(hex_decode(encrypted.substr(16, 16)));
    SymmetricKey key = derive_key(password);
    string ciphertext = encrypted.substr(64);

    // set up AES-CCM cipher
    CCM_Decryption ccm(key, iv, 8, 13); // specify the tag length and nonce length

    // decrypt message using AES-CCM
    Pipe pipe(new AuthenticatedDecryptionFilter(ccm, new StringSink(ciphertext)));
    pipe.process_msg(ciphertext);
    if (!pipe.remaining()) {
        throw runtime_error("Error: Could not decrypt message using AES-CCM!");
    }
    string decrypted = pipe.read_all_as_string();

    return decrypted;
}

int main()
{
    try {
        // use a cryptographically secure PRNG such as the one provided by the Botan library
        AutoSeeded_RNG rng;
        cout << "Enter password: ";
        string password;
        getline(cin, password);

        string message;
        string encrypted_message;
        string decrypted_message;

        while (true) {
            cout << "Enter 'e' to encrypt a message, 'd}
catch (const exception& e) {
cerr << "Error: " << e.what() << endl;
return 1;
}
return 0;
} 
