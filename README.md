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
| `VideoCapture()` | Accesses live camera feed or video file input. |
| `threshold()` | Performs binary segmentation of cap areas. |
| `morphologyEx()` | Applies morphological opening/closing to clean noise. |
| `findContours()` | Extracts connected components (cap outlines). |
| `minAreaRect()` | Determines minimal bounding rectangles for tilt angle estimation. |
| `floodFill()` | Removes holes and fills cap regions before contour detection. |

---

## Workflow  

### Initialization (`initial()`)  
- Captures the label region to define bottle boundaries.  
- Applies binary conversion and flood-fill cleanup.  
- Determines detection range based on label edge coordinates.  

### Cap Detection (`cap_scan()`)  
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
| No Bottle Detected | No bottle identified within the detection region | ![No Bottle Detected](Img/No bottle_detected.jpg) |
| Normal Cap | Cap is properly tightened and fully sealed on the bottle neck | ![Normal Cap](Img/Normal_Cap.jpg) |
| Crooked Cap | Cap is loosely tightened and appears tilted on the bottle neck | ![Crooked Cap](Img/Crooked_Cap.jpg) |
| High Cap | Cap is incompletely tightened (sitting high or partially threaded) | ![High Cap](Img/High_Cap.jpg) |
| Missing Cap | Bottle detected, but no cap region found | ![Missing Cap](Img/Missing_Cap.jpg) |

---

## Lessons Learned  
Through this project, I gained hands-on experience with **image preprocessing**, **morphological filtering**, and **object contour analysis** in industrial vision applications.  
Iterative debugging improved detection accuracy and logic flow, building a solid foundation for future machine vision research.  

---

## Tools & Environment  
- **Language:** C++  
- **Library:** OpenCV  
- **IDE:** Visual Studio  
- **Platform:** Windows  
- **Camera:** External USB Camera  

---

## 📁 Repository Structure  

