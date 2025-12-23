# WALL-E – Robot Sanitation Worker

Inspired by *WALL-E*, this project focuses on the development of an **autonomous sanitation robot** capable of detecting and removing waste from a bounded area while remaining safely inside it.

The robot is implemented on the **E-Puck 2** platform and operates in **real time** using an **RTOS (ChibiOS)**.

## Project Overview

<img src="images/walle.png" alt="WALL-E cleaning zone" width="400">


## Objective

The working area is defined by a **black circular boundary** on the ground.  
**Cardboard cubes** represent waste to be removed.

The robot must:
- detect waste **inside** the working area,
- push waste **outside** the circular boundary,
- **never leave** the working area,
- automatically return to the **center**, marked by a **red dot**.

## General Operation

The robot’s behavior relies on a combination of **sensors**, **real-time processing**, and a **modular software architecture**.

### Waste Detection
- Uses a **Time-Of-Flight (TOF)** sensor  
- Scans the environment by rotating in place  
- Objects detected outside the circular boundary are ignored  

### Boundary Detection
- Color analysis using the **camera**  
- Detection of the **black boundary** using intensity thresholding  
- Automatic backward motion when the boundary is detected  

### Center Repositioning
- The center is identified by a **red visual marker**  
- Detection based on a **differential method** between the red and green color channels  
- Position correction to re-center the robot  

## Software Architecture

The project is organized around **multiple threads**, each dedicated to a specific task:

- `hd_deplacement.c`: basic motion control (forward, backward, rotation)
- `hd_tof.c`: TOF sensor management and object detection
- `hd_cam.c`: image processing and color detection
- `main.c`: module initialization and thread execution

All threads run with **normal priority**, which is sufficient for this application.

## Hardware Add-ons

Several hardware extensions were added:
- A **tilted metal front plate** to push objects outside the circular boundary
- A **mirror** to allow the camera to observe the ground
- A **battery-powered white LED** to ensure stable lighting conditions

These design choices illustrate the trade-off between **hardware and software** solutions in embedded robotics.

## Technologies Used

- **E-Puck 2**
- **ChibiOS (RTOS)**
- **C programming language**
- **Time-Of-Flight sensor**
- **RGB camera**
- **Multi-threaded programming**
- **Real-time embedded systems**

## Results

The robot successfully cleans the defined working area.

Some limitations remain:
- sensitivity to lighting conditions
- occasional instability in red color detection
- minor trajectory deviations due to added hardware weight

Despite these limitations, the project is considered **functional and successful**.

## Authors

- **Melvyn Huynh**  
- **Alexandre Dao**

