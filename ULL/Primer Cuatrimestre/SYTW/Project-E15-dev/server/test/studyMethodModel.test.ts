import mongoose from 'mongoose';
import { MongoMemoryServer } from 'mongodb-memory-server';
import StudyMethodModel from '../models/studyMethodModel';

let mongoServer: MongoMemoryServer;

beforeAll(async () => {
    mongoServer = await MongoMemoryServer.create();
    const mongoUri = mongoServer.getUri();
    console.log("Connecting to MongoDB at: ",mongoUri);
    await mongoose.connect(mongoUri);
});

afterAll(async () => {
    await mongoose.disconnect();
    await mongoServer.stop();
});

describe('StudyMethodModel Tests', () => {
  beforeEach(async () => {
      await StudyMethodModel.deleteMany({});
  });

  test('debe crear un método de estudio válido', async () => {
      const validStudyMethod = {
          name: 'Pomodoro',
          description: 'Técnica de estudio con intervalos',
          workDuration: 25,
          breakDuration: 5
      };

      const savedStudyMethod = await StudyMethodModel.create(validStudyMethod);
      expect(savedStudyMethod._id).toBeDefined();
      expect(savedStudyMethod.name).toBe(validStudyMethod.name);
      expect(savedStudyMethod.description).toBe(validStudyMethod.description);
      expect(savedStudyMethod.workDuration).toBe(validStudyMethod.workDuration);
      expect(savedStudyMethod.breakDuration).toBe(validStudyMethod.breakDuration);
  });

  test('debe fallar al crear un método sin nombre', async () => {
      const invalidStudyMethod = {
          description: 'Método sin nombre',
              workDuration: 30,
              breakDuration: 10
          
      };

      await expect(StudyMethodModel.create(invalidStudyMethod))
          .rejects
          .toThrow();
  });

  test('debe fallar al crear un método sin descripción', async () => {
      const invalidStudyMethod = {
          name: 'Método Test',
          workDuration: 30,
          breakDuration: 10
          
      };

      await expect(StudyMethodModel.create(invalidStudyMethod))
          .rejects
          .toThrow();
  });

  test('debe permitir crear un método con configuraciones por defecto', async () => {
      const studyMethod = {
          name: 'Método Simple',
          description: 'Un método simple sin configuraciones',
          workDuration: 50,
          breakDuration: 10
          
      };

      const savedStudyMethod = await StudyMethodModel.create(studyMethod);
      expect(savedStudyMethod._id).toBeDefined();
      expect(savedStudyMethod.workDuration).toBeDefined();
      expect(savedStudyMethod.breakDuration).toBeDefined();
  });
});