# ArrayTranslation


## 🛠️ Array Transformation (MFC/C++)

A Windows application for geometric pattern generation using MFC, currently implementing **translation logic** with other array operations under development.

### Current Implementation
✅ **Working Features:**
- 2D Translation of rectangular arrays
- Dynamic parameter control (object count, X/Y excursion)
- Drawing area visualization


### Technical Details
```cpp
// Core Translation Parameters (Implemented)
int m_TotalObjects;       // Number of objects in array
double m_XExcursion;      // Horizontal spacing
double m_YExcursion;      // Vertical spacing

// UI Controls (Partial Implementation)
CButton m_ZShape;         // Shape selection toggle
CStatic m_DrawingArea;    // Visualization canvas
