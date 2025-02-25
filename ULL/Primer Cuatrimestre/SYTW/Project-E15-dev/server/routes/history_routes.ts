import express from "express";
import History from "../models/history_model";
import { Request, Response } from "express";


const router = express.Router();

// Obtener todo el historial
router.get("/", async (req: Request, res: Response) => {
    try {
        const history = await History.find({},'userId methodId subjectId workDuration breakDuration date');
            // .populate("userId", "name email")
            // .populate("methodId", "name workDuration breakDuration")
            // .populate("subjectId", "name type_education");
        res.status(200).json(history);
    } catch (error) {
        if (error instanceof Error) {
            res.status(500).json({ error: error.message });
        } else {
            res.status(500).json({ error: 'Error Interno del Servidor' });
        }
    }
});


// Obtener historial del usuario
router.get("/:userId", async (req: Request, res: Response) => {
  try {
    const userId = req.params.userId;
    const history = await History.find({ userId },'userId methodId subjectId workDuration breakDuration date');
    res.status(200).json(history);
  } catch (error) {
    res.status(500).json({ message: "Error al obtener el historial", error });
  }
});

// Guardar sesión
router.post("/", async (req: Request, res: Response ) => {
  try {
    const { userId, methodId, subjectId, workDuration, breakDuration } =
      req.body;

    const newSession = new History({
      userId,
      methodId,
      subjectId,
      workDuration,
      breakDuration,
    });

    const savedSession = await newSession.save();
    res.status(201).json(savedSession);
  } catch (error) {
    res.status(500).json({ message: "Error al guardar la sesión", error });
  }
});

export default router;
