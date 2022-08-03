# Team PENCIL presents
## The (TBD)
Is a device that is capable of detecting gas leaks, bleach leaks, and fires inside a home!
## The Team 
In order to make this device, we had to have a team that was both knowledgable as well as innovative, ##qualities that can be found in all of us. Dhiren was our main man for photographs and keeping track of our progress along the way. Ranvir was the guy for anything python related but he also crunched the numbers for our data analysis. Rushil was our hardware guy who also hanled most of the Arduino code. 
## The Hardware
This device contains a plethora of hardware parts that are required to make it the best that it can be!
### The Case
![IMG_4376-1](https://user-images.githubusercontent.com/80157888/182253272-2f10001b-65ea-4124-89e1-980ccb9a6097.jpeg)
The case for this device is a 3D printed dodecahedron with the bottom being printed out of black PLA and the top being printed out of gold PLA. It features a frosted acrylic front panel to be able to diffuse the lights from the LEDs softly and effectively for the user. 
### The Screen
![IMG_4413](https://user-images.githubusercontent.com/80157888/182253743-d0ebeaeb-e11c-4d85-bbd3-17bc2734fadc.jpeg)
This device features a 1.8" TFT Screen that has a full color spectrum as well as a 128x160 screen resolution. It uses an SPI interface in order to connect to the ESP32 board and display the status of the home. Use of the Adafruit ST7735 library made the integration of this screen into our product much easier by providing easy to understand functions and actions. 
### The DFPlayerMini
![IMG_4406](https://user-images.githubusercontent.com/80157888/182258068-b4b3db27-2f83-4a02-8806-515f549ee598.jpeg)
The board above is a DFPlayerMini, a compact yet powerful driver board for a speaker. It uses a TF card in order to store and play MP3 files to a speaker and connects to the ESP32 via the RX and TX pins onboard.
### The Speaker
![IMG_4416](https://user-images.githubusercontent.com/80157888/182260272-a27e4e1b-34a4-4b83-98f6-b4d9a2faabfe.jpeg)
Paired with the DFPlayerMini is a 5W 4Ohm speaker from Logitech. Taken from a pair of Logitech S120 computer speakers, this speaker features a clear and crisp sound that makes it easy to hear anywhere in the house in the event of a need for evacuation. 
### The LEDs
![IMG_4408](https://user-images.githubusercontent.com/80157888/182253741-e4c3c389-4307-4755-b65d-f25eb8e1de3d.jpeg)
We used some WS2812B LEDs in order to display a color that would indicate the status of the home. These LEDS are super bright and use the full color spectrum! Integration is super simple via the use of the FastLED library which allows us to control the LEDs with a few simple commands.
### Data Collection
![Screenshot 2022-08-01 135024](https://user-images.githubusercontent.com/110428822/182686444-dcadcb55-4f79-48ac-8820-647a7fdab9e6.png)
![pasted image 0](https://user-images.githubusercontent.com/110428822/182686543-4df9b7d9-b759-4ca1-aede-1d7a8ede1c3b.png)
<img width="445" alt="image" src="https://user-images.githubusercontent.com/110428822/182688620-21195588-37e5-4401-b1fc-c2118fc0500c.png">
We used this image
<img width="445" alt="image" src="https://user-images.githubusercontent.com/110428822/182690124-f2b63ef4-6e42-4ca4-aeed-609cad2960e0.png">
<img width="440" alt="image" src="https://user-images.githubusercontent.com/110428822/182690384-f9c48e31-42d3-4899-a970-e61183c14f8b.png">
<img width="443" alt="image" src="https://user-images.githubusercontent.com/110428822/182690454-f659a307-3ba5-4a50-9804-883f96e7e804.png">
<img width="442" alt="image" src="https://user-images.githubusercontent.com/110428822/182690651-4b36ec2a-1949-4c6d-9410-8b3f983b9183.png">
<img width="441" alt="image" src="https://user-images.githubusercontent.com/110428822/182690713-3952e303-23fb-45b4-aa78-636890895f46.png">
<img width="445" alt="image" src="https://user-images.githubusercontent.com/110428822/182690899-e512b0ab-6c38-4fbd-a077-a9d533f116c7.png">


