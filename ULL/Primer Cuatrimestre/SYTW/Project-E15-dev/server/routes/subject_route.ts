import express from 'express';
import Subject from './../models/subject_model'
import { Request, Response } from "express";
const router = express.Router();

router.post('/', async (req, res) => {
  try {
    const subject = new Subject(req.body);
    await subject.save();
    res.status(201).send(subject);
  } catch (error) {
    res.status(500).send(error);
  }
});

router.get('/', async (req, res) => {
  try {
    const subjects = await Subject.find();
    res.status(200).send(subjects);
  } catch (error) {
    res.status(500).send(error);
  }
});

router.get('/:id', async (req: Request, res: Response)=> {
    try 
    {
    const subject = await Subject.findById(req.params.id);
    if (!subject) {
      res.status(404).send();
    }
    else
      res.status(200).send(subject);
  } catch (error) {
      res.status(500).send(error);
  }
});

router.put('/:id', async (req: Request, res: Response) => {
  try {
    const subject = await Subject.findByIdAndUpdate(req.params.id, req.body, { new: true, runValidators: true });
    if (!subject) {
      res.status(404).send();
    }
    else
    res.status(200).send(subject);
  } catch (error) {
    res.status(500).send(error);
  }
});

router.delete('/:id', async (req: Request, res: Response) => {
  try {
    const subject = await Subject.findByIdAndDelete(req.params.id);
    if (!subject) {
      res.status(404).send();
    }
    else
    res.status(200).send(subject);
  } catch (error) {
    res.status(500).send(error);
  }
});

router.delete("/", async (req: Request, res: Response) => {
    try {
        await Subject.deleteMany({});

        res.status(200).json({ message: 'Todas las materias han sido eliminadas correctamente' });
    } catch (error) {
        res.status(500).json({ error: 'Error Interno del Servidor' });
    }
});

module.exports = router;
