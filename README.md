# Team PENCIL presents
## The Sharpener
The Sharpener is a device that is capable of detecting gas leaks, bleach leaks, and fires inside a home! This is for homeowners to let them know if there is a leak or fire in their house.
## Our Plan
Our plan was to make a device that can detect harmful substances if they are not contained. The first thing we did was brainstorm possible ideas we could do and ended up deciding on the device we're doing right now. After brainstorming, we came up with a design for the case. After we came up with the design of the case, we printed the parts of the case and decided what hardware we were going to use. Then we started programming. After we finished most of the programming, we started running tests for data. After all of that we finished programming the speaker and lights and ran our last test for data.
## The Team 
In order to make this device, we had to have a team that was knowledgable as well as innovative and helpful, ##qualities that can be found in all of us. Dhiren was our main man for photographs and keeping track of our progress along the way. Ranvir was the guy for anything python related but he also crunched the numbers for our data analysis. Rushil was our hardware guy who also handled most of the Arduino code. 
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
## Data Collection
Our sensor detects different gasses by using thresholds and boundries that we created for the gas resistivity. So when the values fell under these boundries/threseholds it would run the alert code. To determine these thresholds and boundries we have to collect data of the gasses and create the thresholds after analyzing the data. We used two heat profiles, hp-354 and hp-411, we decided to use the one that we liked the most or appealed to us in our final code the most but we ran trials and data collection with both heat profiles. We measured the gas resitivity of the room, the smoke emmitted from fire, the smell emmited from gasoline, and the smell emmitted from bleach. We decided to measure normal room gas just to compare our data and see the differences, while we decided to use the other gasses as they are the most harmful to a household. To collect our data we ran python code and used the serial monitor to collect values. After evaluating both we decided to use the serial monitor values as they seemed easier to read and easier to build our threseholds around. One problem we had during data collection is that our sensor fell into the gasoline, so it would permanently read wrong values. In result of this, we had to get a new sensor and redo each trial because we figured that the new sensor would read different values from the previous one.
### Excel Graphs
<img width="500" alt="image" src="https://user-images.githubusercontent.com/110428822/182688620-21195588-37e5-4401-b1fc-c2118fc0500c.png">

For the Hp-354 we saw a similar trend in all of the gasses the only difference was the amount of gas resistivity. For the normal room temperature atmosphere we see after the first step the gas resistivity spikes up majorilly but, gradually decreases from 7000/8000 to 2000/3000 which then after the values decrease to around 200 and continue to decrease until step 8, which then they increase to 100. After doing many experiences we figured that the gases in each room differ a lot so we decide to record values in the same room. The purpose of the Hp-354 normal readings is to compare them to the other gasses and other heat profiles. It also known as the 'constant' reading.

<img width="500" alt="image" src="https://user-images.githubusercontent.com/110428822/182690124-f2b63ef4-6e42-4ca4-aeed-609cad2960e0.png">

For the Hp-354 we saw a similar trend in all of the gasses the only difference was the amount of gas resistivity. For the Bleach the trend and values are very similar to the normal readings, the only difference being that the readings for the gas resistivity is slightly higher when compared to the normal values, which would mean we would have to keep our thresholds for the bleach to be very small in order to prevent overlapping with the normal values.

<img width="500" alt="image" src="https://user-images.githubusercontent.com/110428822/182690384-f9c48e31-42d3-4899-a970-e61183c14f8b.png">

For the Hp-354 we saw a similar trend in all of the gasses the only difference was the amount of gas resistivity. The difference in the gas values and the bleach and normal values is that it's significantly smaller and it's smaller than the fire values as well even though you could assume that they would be pretty much the same. In summary, the gas values were the most unique to us.

<img width="500" alt="image" src="https://user-images.githubusercontent.com/110428822/182690454-f659a307-3ba5-4a50-9804-883f96e7e804.png">

The fire has higher values than the gas but lesser values than the bleach, so it's basically in the middle between these two. Measuring the fire was quite difficult because we had to start a fire, then choke it, then record the values using the leftover smoke, but the smoke would diminish pretty quick, so it would be hard for the sensor to read proper values, so it took multiple tries.

<img width="500" alt="image" src="https://user-images.githubusercontent.com/110428822/182690651-4b36ec2a-1949-4c6d-9410-8b3f983b9183.png">

The heat profile Hp-411 was different than Hp-354 because most of the steps in Hp-411 were a lot less and significant than Hp-354's steps.

<img width="500" alt="image" src="https://user-images.githubusercontent.com/110428822/182690713-3952e303-23fb-45b4-aa78-636890895f46.png">

The difference between Hp-411's values for bleach and Hp-354's values for bleach was that Hp-411 had lower values, but Hp-411's values for bleach was higher than the normal Hp-411. Hp-411 bleach was a bit more consistent than Hp-354 bleach. This might have happened because of environmental changes.

<img width="500" alt="image" src="https://user-images.githubusercontent.com/110428822/182690899-e512b0ab-6c38-4fbd-a077-a9d533f116c7.png">

Hp-411 fire values has a similar trend to bleach and normal gasses/atmosphere, but it has lower values than both. Hp-411 fire values were somewhat easier to record as after many trial with the Hp-354 fire values, we got the hang of it.

### Python Graphs
These are our python graphs and they were helpful to somewhat until we found out that the graphs weren't as helpful to us as we needed them so we thought we shouldn't analyze them.
#### HP-354
![Screenshot 2022-08-01 150747](https://user-images.githubusercontent.com/110428822/183178385-a39f93a1-03f8-4f25-ab38-c60502f6a718.png)


![pasted image 0](https://user-images.githubusercontent.com/110428822/183179895-dff4eafc-1e56-48ce-afaa-a0c6399f0309.png)



![Screenshot 2022-08-01 135024](https://user-images.githubusercontent.com/110428822/183186130-df86e44d-33b8-4cab-ab5f-61860a251ca3.png)
#### HP-411


![Screenshot 2022-08-02 105006](https://user-images.githubusercontent.com/110428822/183183324-b08c11ec-672a-498f-a2cf-a4a42db36886.png)


![Screenshot 2022-08-02 105006](https://user-images.githubusercontent.com/110428822/183187809-cfc2d6d7-49f7-4713-b45c-da28b552115e.png)



![Screenshot 2022-08-03 135837](https://user-images.githubusercontent.com/110428822/183188406-0c8c6326-92b1-4b35-8267-fbe9edd51cc7.png)


