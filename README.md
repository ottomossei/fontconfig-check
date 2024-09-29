# fontconfig-check

This project provides a basic library to interact with `fontconfig`, allowing you to find font files based on font names. Additionally, it includes an optional image generation module that uses the found font to render text into an image. The project is designed to be modular, with the image generation functionality enabled or disabled through build options.

## Features

- **Font File Lookup**: Use `fontconfig` to find the file path of a font based on its name.
- **Modular Design**: The project is modular, with an optional image generation module that can be enabled or disabled during the build.
- **Image Generation (Optional)**: If enabled, the image generation module uses `FreeType` and `Cairo` to render text using the found font into a PNG image.

## Prerequisites

- C++14 compatible compiler
- CMake 3.10 or higher
- The following libraries:
  - `fontconfig`
  - `freetype2` (if use image_generation)
  - `cairo` (if use image_generation)

On Ubuntu, you can install these dependencies using:

```bash
sudo apt-get install libfontconfig1-dev
```

## Build Instructions
Create a build directory and run CMake:
```bash
mkdir build
cd build
cmake .. -DWITH_IMAGE_GENERATION=OFF -DCMAKE_BUILD_TYPE=Release
make
```

## Running the Example
After building, run the example program:

```bash
./example/fontconfig_example
```
If the image generation module is enabled, the program will create an output PNG image with the text rendered using the found font.

## Usage
Font Lookup
The main library allows you to find font files based on the font name using the FontconfigCheck class. Here's an example:

```cpp
FontconfigCheck fontChecker;
std::string fontFile = fontChecker.findFontFile("Arial");

if (!fontFile.empty()) {
    std::cout << "Font file found: " << fontFile << std::endl;
}
```

## Image Generation (Optional)

If image generation is enabled during the build, the library can render text into an image using the found font. This functionality is provided by an additional module that leverages the `FreeType` and `Cairo` libraries for rendering. The generated image is saved as a PNG file. This feature is particularly useful for rendering custom text using a specific font found through `fontconfig`.

### Enabling Image Generation

To enable the image generation module, you need to pass the option `-DWITH_IMAGE_GENERATION=ON` when configuring the project with CMake. This will build the image generation module and link it to the main library. Make sure that the required dependencies (`libfreetype6-dev` and `libcairo2-dev`) are installed on your system.

```bash
sudo apt-get install libfreetype6-dev libcairo2-dev
```
Configure the project with the image generation feature enabled:
```bash 
cmake .. -DWITH_IMAGE_GENERATION=ON  -DCMAKE_BUILD_TYPE=Release
```


## Image Generation (Optional)

If image generation is enabled during the build, the library can render text into an image using the found font. This functionality is provided by an additional module that leverages the `FreeType` and `Cairo` libraries for rendering. The generated image is saved as a PNG file. This feature is particularly useful for rendering custom text using a specific font found through `fontconfig`.

### Enabling Image Generation

To enable the image generation module, you need to pass the option `-DWITH_IMAGE_GENERATION=ON` when configuring the project with CMake. This will build the image generation module and link it to the main library. Make sure that the required dependencies (`libfreetype6-dev` and `libcairo2-dev`) are installed on your system.

```bash
sudo apt-get install libfreetype6-dev libcairo2-dev
```
Configure the project with the image generation feature enabled:

```bash
cmake .. -DWITH_IMAGE_GENERATION=ON -DCMAKE_BUILD_TYPE=Release
```

### Using the Image Generation Module
Once the image generation module is enabled and built, you can use it in your application to render text into an image. Here is an example of how to use the ImageGenerationModule in your code:

```cpp
// Create an instance of the image generation module, specifying the font file,
// the text to render, and the output image file (output.png).
auto imgGen = std::make_unique<ImageGenerationModule>(fontFile, "Hello, World!", "output.png");

// Add the module to the font checker instance.
fontChecker.addModule(std::move(imgGen));

// Execute all modules, including the image generation.
fontChecker.runModules();

```