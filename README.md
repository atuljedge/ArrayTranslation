## 🔄 Drawing Pipeline Workflow

```mermaid
graph TD
    A[ClearDrawingArea] -->|CDC& dc| B[Draw Axes]
    B --> C[DrawRectangles]
    C --> D{Boundary Check}
    D -->|Within Bounds| E[Render Next Rectangle]
    D -->|Exceeds Bounds| F[Stop Rendering]
    E --> C
    style A fill:#4CAF50,stroke:#388E3C
    style B fill:#2196F3,stroke:#0b7dda
    style C fill:#FF9800,stroke:#e68a00
    style D fill:#f44336,stroke:#d32f2f
