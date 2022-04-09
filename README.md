# Group assignment: wall follower
This is your second group assignment. Please follow the exact instructions
below to receive full points. It is important that you create > 10
commits for each demonstration. ** If you copy and paste code, and push it with
a single commit, you risk earning a low grade. ** Individual and group grades may vary.

## Background and preparation
Collect your sensor kit from the lab staff. There is a rack filled with green boxes; each box contains
all electronics that is required for RBE 2002.

Your [IR distance sensor](https://www.pololu.com/file/0J85/gp2y0a21yk0f.pdf) has three pins (signal, GND, and VCC (+5V)). Connect the signal pin of your
IR distance sensor to pin A0 on your 32U4 control board (see Figure below). **Although you will not need your
sonar sensor just now**, you might want to connect it. Your sonar distance sensor has four pins 
(VCC (+5V), TRIG, ECHO, and GND). Connect the TRIG to pin 0, and ECHO
pin to pin 1 on your 32U4 control board (see Figure below). The IR and sonar distance sensors
operate at 5V. Therefore, connect 5V and GND to the pins (see Figure below). If you cannot find a 
second 5V connection, use the ``LCD Contrast`` pin and set it to 5V by adjusting the potentiometer 
next to the pin header using a screwdriver. A multimeter might be helpful here.

![sonar](https://user-images.githubusercontent.com/68814774/160877934-033aab0a-def8-419c-98ee-fb317c56ef34.jpg)

![IR](https://user-images.githubusercontent.com/68814774/160877967-d50bc62f-7f11-4331-be22-cce4df206b68.jpg)

![atmega](https://user-images.githubusercontent.com/68814774/160877984-42be8378-b164-4219-a6cc-562cb655a4f6.jpg)

For the lab, you need to place the IR sensor at an angle of 45 degrees as shown in the Figure below. In this
setup, distance decreases when the robot is heading towards the wall, and distance increases when
the robot is heading away from the wall. For this lab activity and demonstration, we will only use
the IR distance sensor for wall following.

![IR-sensor-position](https://user-images.githubusercontent.com/68814774/160881593-ca7ba55f-90c8-4550-90fd-e2f78e669097.jpg)

## Step 1: each team member: clone this repository to your computer
Clone this repository to your local machine.
```
git clone <PASTE THE REPO ADDRESS HERE>
```
## Step 2: each team member: open the cloned project in VS Code
Open the repository that you just cloned in MS Visual Studio Code. Your Platform IO plugin should be working at this stage.

## Step 3: each team member: upload the program to your Romi
Once uploaded, your Romi should output "Robot idle" in your terminal. After you press button A 
on your Romi board, this message should change to "Distance measurement". Essentially, you are provided
with an example of a simple state machine, which you can use for your individual
and group assignments. Try to understand the implementation of the state machine, before
proceeding to the next step. If you cannot get the terminal to output the messages as 
described above, please ask for help from your group members or SAs in one of their lab 
sessions or office hours.

## Step 4: each team member: create personal file in user folder
Each group member has to create a txt file and the **name** of the file must contain
the student's name and student id. Either create the file manually, or do it via the 
terminal all together:

```
git pull
cd users
touch user-id_last-name.txt
git add --all 
git commit -m "I added my user id and name file"
git push
```

## Step 5: each team member: create a branch and program demo 1
Each group member will have to program their own demo 1. Therefore you need to
create your own branch from the remote group repository. As a branch name, use your 
first dash last name "FIRST-LAST" (e.g., MARKUS-NEMITZ). Steps 5-8 cover demo 1.

```
git checkout -b "your-branch-name"
git branch
```

The terminal will confirm that you are in your own personal branch. Once you see this 
confirmation, add a line to the main.cpp file:

```
//this is my version of the group assignment
```

Now add, commit, and push the code to your group repository:

```
git add -A
git commit -m "this is my own version of the git repository; I am safe to make 
changes here"
git push -u origin "your-branch-name"
```

Check your group repository in the browser. You should be able to see the repo
and a branch with your name (You may need to refresh the page).

## Step 6: each team member: take measurements to convert ADC values from IR sensor to actual distances
First, you need to convert the measurement values from your IR sensor into
actual distances. For the IR
sensor, we could determine polynomials that fit either (distance) or (1/distance) characteristics
curves. However, since two sensors are never actually identical, mostly due to fabrication
tolerances, characterization is our preferred method.

Place your robot at defined distances (using a ruler, which is included in the kit you just grabbed in 
your lab session), and record distance measurements. Calculate the average value of each distance (min. 10 measurements per distance) and determine the linear relationship using y = a * x + b for distances between 8 cm and 80 cm. Put the inverse of the distance on your x-axis, i.e., 1/distance. This trick will allow you to define the transfer function of your IR distance sensor as a linear function, as opposed to a more complicated polynomial. You will have to decide how many distance measurements you
take to develop the calibration curve. Generally speaking, the more data points you average at a given
distance, the more trustworthy becomes your calibration curve.

![Screen Shot 2022-03-30 at 12 31 49 PM](https://user-images.githubusercontent.com/68814774/160885630-bcbe95c4-088d-482c-84ea-cb8e82a9b14d.png)

## Step 7: each team member: program a class for your IR sensor
At this stage, you have a term for a linear relationship betweeen distance and voltage measurements. Now, finish programming ``IR_sensor.cpp`` and ``IR_sensor.h``. Program the following functions: ``void IRsensor::Init(void)`` in which you setup your microcontroller pin (i.e., ``pinMode(pin_IR, INPUT);``, whereas you have to define ``pin_IR = A0``); ``float IRsensor::PrintData(void)``; and ``IRsensor::ReadData`` in which you insert your conversion term from Step 6.

## Step 8: each team member: create an object of your IR class and output measurements
Once you finished programming your IR sensor class, include ``IR_sensor.h`` in your ``main.cpp`` file, create an
object of your new class, and print distances when your ``buttonA`` is pressed.

Demonstrate measurements in the range from 10 cm to 50 cm to a SA. The measurements must be printed to the terminal, and
only occur when ``buttonA`` was pressed.

[SIGN-OFF: 1]

Create a release of your code in GitHub and call it: `demo 1 YOUR-NAME` (e.g., demo 1 NEMITZ). As tag, enter `1.0.X`.

## Step 9: Group discussion
Discuss with your group, who developed the strongest implementation of demo 1. 
What were some pros and cons of that implementation?
That student then creates a pull request in the browser (see exemplarily image below).
    
<img width="726" alt="Screen Shot 2022-03-20 at 8 52 10 PM" src="https://user-images.githubusercontent.com/68814774/159193554-723d103d-df89-4e7d-8852-266da1f0243a.png">

Each group member has to go in detail through the changes, and make comments
or suggestions to the pull request. Once everyone agrees, accept the pull request
and work as a group from your master branch.

```
git checkout master
```

## Step 10: program PD-controller for wall follower
Now, as a group, you need to program a PD controller. Start a [live session](https://code.visualstudio.com/learn/collaboration/live-share) via Visual Studio Code, and ensure that all team members are present. When using live share and commiting code as a group, author attributions should be automatically added in the vscode 'Source Control' menu. If they do not show up (perform a test commit), add them manually (*We will not be able to tell who worked on each commit UNLESS you state so in the commit message. This is important for receiving full points for your individual contribution*).

Prepare demo 2 in which you showcase your Romi to a SA (i) moving along a wall at a distance of 15 cm, (ii) and taking turns around corners successfully.

[SIGN-OFF: 2]

Create a release of your code in GitHub and call it: `demo 2 YOUR-GROUP-NAME`. As tag, enter 2.0.0.

## Step 11: program wall follower that moves at constant speed
Combining your PI-velocity-controller with your PD-wall-following controller, move along a wall at a 
constant speed of 10 cm/s. 

[SIGN-OFF: 3]

Create a release of your code in GitHub and call it: `demo 3 YOUR-GROUP-NAME`. As tag, enter 3.0.0.

![PD-controller](https://user-images.githubusercontent.com/68814774/160889942-2ed3546f-4944-499e-929a-8f4176fa6433.jpg)

