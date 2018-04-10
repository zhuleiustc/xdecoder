# X Decoder

XDecoder is a light ASR(Automatic Speech Recognition) decoder framework. 
X means enchanced, fast, and portable. Our target is running 
LVCSR(Large Vocabulary Continuous Speech Recognition) on low resourse system,
especially on mobile phones and other embedding device. 

So serveral things should be taken into account.

- **Mini**, the whole package(AM, LM, lib) of the system should be small.
- **Fast**, Recognition speed should be in real time
- **Low power**, which is critical for modern mobile phones.


## Solutions

This is our solutions for the above requirements.

- **Mini**
    1. AM, we will use quantizaton to reduce the model. 
       The model size can be reduced to 1/4 if we use 8 bits quantization. And we can use SVD to compress the model further.
    2. LM, LM here means the decoding FST file. Small LM should be used in our scenario. The basic unit of FST is arc, 
       which is a tuple(ilabel, olabel, weight, next_state) with four elements in nature. And ilabel, olabel, next_state are int32 type, 
       so we can use varint to reduce it.
    3. lib, the third party library should be as less as possible.

- **Fast**




