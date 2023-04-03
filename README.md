# image_processor

image_processor

requirements for image:

-bmp file format

-24 bits per pixel

-no compression

-BITMAPINFOHEADER DIB header

Usage: ./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5

Available filters:

-crop width height

Crop the image to the specified width and height. The top left of the image is used.
If the requested width or height exceeds the dimensions of the original image, the available part of the image is returned.

-gs

Converts an image to grayscale.

-neg

Converts an image to negative.


-sharp

Sharpening.

-edge

Edge detection. Pixels with a value more than threshold are painted white, the others are painted black.

-blur sigma

Gaussian blur with parameter sigma.