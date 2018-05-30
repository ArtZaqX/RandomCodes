# RandomCodes
General and random projects.
* C++ Types Decoder: 
  * Does not support functions with arguments, custom types, const, type keywords except int, float, void. Does not check if types are valid. 
  * Algorithm: Start from identifier. Move right and keep decoding symbols until `;` is found. If `)` is found, move left and decode the symbols until *corresponding* `(` is found and then continue after the `)` towards right. Then move left without reading already decoded symbols and stop when start of line is reached.
* FileIO: A class for reading/writing a whole file at the same time. 
