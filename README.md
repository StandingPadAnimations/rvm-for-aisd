# RVM for AISD
An attempt to bring Resurgence to the Swift, Python, and C++ languges.

# Why?
When I created Resurgence, I decided to code it in Rust because of the memory and thread safety gurantees. However, most people in AISD don't know Rust. While a C API exists, C is kinda a pain to deal with (no offense to C developers)

While I could officially support these languages, I don't like the idea of "polluting" Resurgence with wrappers, so instead I created this repo.

## So do I lost the benifits of Resurgence being coded in Rust?
No, because every part of Resurgence (including the C FFI) is coded in Rust. We're simply taking advantage of Resurgence's C API and the fact that most major languages support C.
