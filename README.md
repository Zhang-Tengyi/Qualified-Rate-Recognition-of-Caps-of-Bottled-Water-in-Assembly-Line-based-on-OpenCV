# Qualified-Rate-Recognition-of-Caps-of-Bottled-Water-in-Assembly-Line-based-on-OpenCV


## Overview  
This project presents a real-time bottle cap inspection system built with OpenCV and Visual Studio (C++), using edge detection, contour analysis, and adaptive thresholding to detect tilted, loosely sealed, or missing caps under varying lighting conditions.
It automatically classifies typical defects such as high caps, crooked caps, and improper sealing, while computing real-time qualification rates and defect distributions on bottled water production lines.  

---


## Features  
- **Real-time Detection:** Uses external camera to monitor bottle caps continuously.  
- **Edge & Contour Analysis:** Identifies bottle caps via edge detection, contour extraction, and area filtering.  
- **Defect Classification:** Detects and labels *high caps*, *crooked caps*, *missing caps*, and *normal caps*.  
- **Performance Metrics:** Computes detection count, defect distribution, and qualification rate per test cycle.  
- **Lighting Robustness:** Includes preprocessing, threshold segmentation, and flood-fill filtering to ensure stable detection under varying illumination.


---


## Technical Details  

| Function | Purpose |
|-----------|----------|
| `imread()` | Loads an image from file for testing or calibration. |
| `imshow()` | Displays image frames in real time for visualization. |
| `VideoCapture()` | Acquires live video stream from camera or file input. |
| `split()` | Separates color channels for individual processing. |
| `threshold()` | Performs binary thresholding for segmentation. |
| `morphologyEx()` | Applies morphological operations (open/close/gradient) to remove noise and refine shapes. |
| `findContours()` | Extracts connected components and outlines of detected objects. |
| `contourArea()` | Calculates the area of detected contours for filtering by size. |
| `boundingRect()` | Finds axis-aligned bounding rectangles around contours. |
| `minAreaRect()` | Determines the minimum rotated rectangle to measure cap tilt angles. |
| `floodFill()` | Fills holes and smooths segmented regions to improve detection accuracy. |


---

## Workflow  

### Initialization 
- Captures the label region to define bottle boundaries.  
- Applies binary conversion and flood-fill cleanup.  
- Determines detection range based on label edge coordinates.  

### Cap Detection 
- Processes each bottle’s cap region individually.  
- Analyzes the number and orientation of detected rectangles.  
- Classifies cap condition as *normal*, *tilted*, *high*, or *missing*.  

### Result Computation  
- Press **Tab** → Calculate the current batch’s defect ratios and pass rate.  
- Press **Enter** → Summarize total detection statistics.  
- Press **ESC** → End inspection.


---

## Results  

| Status | Description | Example |
|---------|--------------|---------|
| No Bottle Detected | No bottle identified within the detection region | ![No Bottle Detected](Img/No_bottle_detected.png) |
| Normal Cap | Cap is properly tightened and fully sealed on the bottle neck | ![Normal Cap](Img/Normal_Cap.png) |
| Crooked Cap | Cap is loosely tightened and appears tilted on the bottle neck | ![Crooked Cap](Img/Crooked_Cap.png) |
| High Cap | Cap is incompletely tightened (sitting high or partially threaded) | ![High Cap](Img/High_Cap.png) |
| Missing Cap | Bottle detected, but no cap region found | ![Missing Cap](Img/Missing_Cap.png) |


---


## Tools & Environment  
- **Language:** C++  
- **Library:** OpenCV  
- **IDE:** Visual Studio  
- **Platform:** Windows  
- **Camera:** External USB Camera  


---
