import express from 'express';
const morgan = require("morgan");
const mongoose = require('mongoose');
const bodyParser = require('body-parser');
import dotenv from 'dotenv';
import cors from 'cors';

import methodRoutes from './routes/study_method_routes';
import historyRoutes from './routes/history_routes';

// Cargar las variables de entorno
dotenv.config();

export const app = express();
const mongoURI = process.env.ATLAS_URI;
app.use(morgan("dev"));


if (!mongoURI) {
  console.error('La URI de MongoDB no está definida.');
} else {
  console.log('Conectando a MongoDB:', mongoURI);
}

mongoose.connect(mongoURI)
  .then(() => {
    console.log('Conectado a MongoDB Atlas exitosamente');
  })
  .catch((error: unknown) => {
    console.error('Error al conectar a MongoDB:', error);
  });
// Settings

app.set("port", process.env.PORT || 5300);

// Middleware
app.use(express.json()); // para interpretar json
app.use(bodyParser.json());
app.use(cors({
  origin: 'http://localhost:5173', 
  methods: ['GET', 'POST', 'PUT', 'DELETE'],
  allowedHeaders: ['Content-Type', 'Authorization']
}));

// Routes
app.use('/user',require("./routes/user_route"));
app.use('/method', methodRoutes);
app.use('/subject', require("./routes/subject_route"));
app.use('/history', historyRoutes);

const servers = app.listen(app.get("port"), () => {
  console.log(`Server running at http://localhost:` + app.get("port"));
});

export {servers};