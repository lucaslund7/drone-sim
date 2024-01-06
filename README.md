Our work can be seen in the .cc files located in lib/transit/include and lib/transit/scr  
Everything else was provided and slightly modified  
  
  
What is the project about?  
    This project is a drone simulation software which allows users to simulate delivering packages to customers. Users can choose a starting position for the package as well as a destination position where the packages owner will wait at. A drone will then be assigned to this package and travel to pick it up. Once the package has been picked up, the drone will bring the package to the owner using a path finding algorithm specified by the user at the time of package creation. The drone will then drop the package to the owner at which time it will go to its next delivery if there is one scheduled or wait for a package to be created. This project is made to teach about multiple different design patterns, with multiple different aspects of the simulation’s logical dependencies, object creation, and relationships between files stemming from different design patterns and principals.  
  
How to run the simulation - Run and launch simulation  
    1. Start by being on a UMN CSE Lab machine or SSH into one. Navigate into a directory for this project, our submission uses the directory “Team-010-56-hw4”.  
    2. Inside of a terminal in VSCode add a port, for this example the port “8910” will be used.   
    3. Within the directory terminal (“/path/to/directory/Team-010-56-hw4”) run the terminal command “make -j”.  
    4. At this time, you will see many files being built and compiled. When returned to the standard terminal command prompt run the command   
    “./build/bin/transit_service 8910 apps/transit_service/web/”  
    In this command, the central four digits will be your chosen port. As stated prior, 8910 is the port of this write-up.  
    5. After doing this, lines showing that the simulation has begun will appear. At this time, navigate to a web browser and access the URL  
    “http://127.0.0.1:8910”  
  
How to run the simulation - Using the simulation  
    1. The simulation will load with your initial view being of polygonal buildings. Change where you look as well as the zoom with your cursor or go to the “Change View” box in the top left to select one of the existing entities.  
    2. Select “Schedule Page” from the top left box to launch the scheduling page in a new window.  
    3. When in the scheduling page, the secondary function of adding a new human entity to the simulation can be achieved by selecting “Add Human” at the bottom.  
    4. When in the scheduling page, the primary function of requesting and scheduling a delivery can be achieved using the following steps.  
        i. Type the name of the customer you wish to receive the delivery in the “Name” text box.  
        ii. Use the “Search Strategy” drop-down selection to pick how the drone will navigate to the customer from one of the four provided options.  
        iii. On the map image select the starting location (Where the package will initially be) as well as the destination location (Where the customer will be waiting).  
        iv. Click the “Schedule Delivery” button and navigate back to the simulation tab in your web browser. The simulation will be running with the drone beginning its journey to deliver the package.  
    5. As you desire, possible paths the drone can follow will become alternate visibility by (un)selecting the “Show All Routes” check box in the upper left of the simulation tab.  
    6. As you desire, the simulation speed can be increased or decreased using the “Simulation Speed” slider in the upper left of the simulation tab.  
    7. Step 4 can be repeated as many times as you wish, scheduling more deliveries or adding more humans. When you are satisfied with using the simulation, proceed to step 8.  
    8. On the simulation web page, select “Stop Simulation” to terminate the simulation. While the page will remain visible, entities will no longer move, and deliveries can no longer be scheduled. All simulation related tabs can be shut at this time.  
  
What does the simulation do specifically?  
    The simulation provides a rough visualization of the UMN where deliveries can be scheduled to simulate a drone package delivery service as it would function on campus. Multiple aspects of what this simulation does are listed below:  
        1. Entities – Simulation allows for existence of entities, which are objects that have certain logical properties and functions.  
        2. Drones – A subclass of entity which allows for three-dimensional movement, as well as designated movement strategies and a package it is responsible for transporting.  
        3. Packages – A subclass of entity which is linked to a robot owner. Movement is allowed but relies on a drone which, once connected, dictates its movement strategy.  
        4. Robots – A subclass of entity which is linked to a package, awaits the delivery of this package from a drone.  
        5. Entity Creation and linking – Construct entities when deliveries are scheduled, namely the robot customer and its desired package.  
        6. Path Selection Logic – Assigns different movement strategies for a drone to follow as it delivers a package. Movement strategy is chosen by user when scheduling a delivery.  
        7. Movement Logic – Implements movement logic to dictate where to go at a given point, along with when the user set strategy should be followed.  
        8. Joint Entity Movement Logic – Implements joint entity movement logic to decide how movement should occur depending on its current relationship status with other entities.  
        9. Celebration Movement Logic – Implements celebration movement logic to decide what celebration should be performed as well as when celebration should occur.  
        10. Simulation Speed Manipulation – Allows for simulation speed to be altered, along with properly updating front-end visuals and back-end logic to compensate for these changes.  
  
New Feature 1 - Notifications  
    1. The notifications feature is made to provide front-end information about what a drone is currently doing.  
    2. This is signifigantly interesting because users are able to get real time updates when the drone has some sort of signifigant change occur.  
    3. It adds to the existing work by linking itself to the entity and specifically, the drone class. It relies on actions taken by the drone and the current status of the drone's various attributes to determine what message should be printed out.  
    4. The pattern chosen for this was the observer pattern since that is the pattern which directly deals with creating notifications for certain events.  
    5. For a front-end user, there are no steps for the drone observer to begin functioning. By default, when a drone is created an observer for that drone is also created. Since the drone observer is a child of an all encompassing entity observer class, back-end users could extend this by adding in observers specific for other subtypes of entities. The drone class has been given a function notify(int situation) which takes in an integer that runs a switch case for the observer. Depending on what switch case occurs, a corresponding message is constructed and will be printed out after verifying it is not a repeated message. Throughout the drone class, such as within its update function and its getNextDelivery function, there are calls to notify with different situation integers to trigger each message.  
  
New Feature 2 - Battery & Recharge  
    1. The battery & recharge feature allow for a drone to work in tandum with a battery. This means that depending on distance traveled and time passed, the drone will be forced to recharge before continuing.  
    2. This is signifigantly interesting since it adds an entirely new level of logic to the drone simulation. It also makes the simulation more realistic, since real world delivery drones would need to be made and programmed with battery level and rechargability into consideration.  
    3. It adds to existing work by having two new type of factory designed to create battery decorators and recharge stations. Recharge stations need to be placed around the simulation model both in back-end functionality as well as front-end visualizations. The battery decorator is used as a wrapper around the drone class, giving it new functionality and logic.  
    4a. The battery was created with the decorator pattern in order to give the drone new behaviors without needing to create a new class that is the exact same as drone but has the battery functionality included within it. This change allows for minimal changes to the current drone class and also has the battery class have a more streamlined header and .cc file.  
    4b. The recharge station was created using the factory method since it allowed for creation of the recharge station object to be one step removed from the recharge station itself and the logic it would be running once it already was created. This allows for a more uniform way of doing things since the other entities (drones, package, robot, human, helicopter) all utilize the factory pattern. It also means that the recharge station classes are easier to read and help follow the S of solid since the creation and usage of the recharge station has been seperated out.  
    5. For front-end users there are no steps to using the new feature. By default, drones are now wrapped in the battery decorator. This gives the drone an attribute which will hold its charge, as well as signal when recharging needs to happen. Once the battery charge has depleted enough, the drone will redirect to go to the nearest recharge station. Once its battery is back to 100% it will continue onto the destination it had prior to recharging its battery. Notifications are also provided about when the drone is going to charge and when it fully has charged.  
  
Sprint Retrospective  
    Our group chose to organize our sprints into two portions, one for the observer work and the other for the battery work. This worked well since it allowed clear distinctions about what category or feature each task fell under. Initially picking jobs using the Jira sprint guide worked well since it provided visual confirmation that each group member had a relatively equal amount of work. If tasked with doing this again there are two things we would likely change. First, think closely about how tasks fall relative to each other and plan them with your schedule. We ran into some scenerios where task X needed to be finished before task Y could start. If person Y has free time early into the sprint, before person X has free time, then person Y will be unable to make use of their time. Next, remembering to put non-programming aspects into the sprint. While we had included things like writing, testing, doxygen, and style guide in our sprints, we did not include things like UML creation or Write-up work, this lead to underestimating the work we had left at any given point.  
  
Notification Feature:
![notificaiton uml](https://github.com/lucaslund7/drone-sim/blob/main/uml/notification_uml.png?raw=true) 


Battery and RechargeStation Feature:
![battery/rechargestation uml](https://github.com/lucaslund7/drone-sim/blob/main/uml/Battery_RechargeStation.png?raw=true) 
