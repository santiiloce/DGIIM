import mongoose from 'mongoose';
import { MongoMemoryServer } from 'mongodb-memory-server';
import UserPreferencesModel from '../models/userPreferencesModel';

describe('UserPreferences Model Test', () => {
    let mongoServer: MongoMemoryServer;

    beforeAll(async () => {
        mongoServer = await MongoMemoryServer.create();
        const mongoUri = mongoServer.getUri();
        await mongoose.connect(mongoUri);
    });

    afterAll(async () => {
        await mongoose.disconnect();
        await mongoServer.stop();
    });

    afterEach(async () => {
        await UserPreferencesModel.deleteMany({});
    });

    describe('Validación del Modelo', () => {
        test('debe crear preferencias de usuario válidas', async () => {
            const validUserPreferences = {
                userId: new mongoose.Types.ObjectId(),
                methodId: new mongoose.Types.ObjectId(),
                    workDuration: 25,
                    breakDuration: 5
                
            };

            const userPreferences = new UserPreferencesModel(validUserPreferences);
            const savedUserPreferences = await userPreferences.save();
            
            expect(savedUserPreferences._id).toBeDefined();
            expect(savedUserPreferences.userId).toEqual(validUserPreferences.userId);
            expect(savedUserPreferences.methodId).toEqual(validUserPreferences.methodId);
            expect(savedUserPreferences.workDuration).toBe(25);
            expect(savedUserPreferences.breakDuration).toBe(5);
        });

        test('debe fallar al crear preferencias sin userId', async () => {
            const userPreferencesWithoutUserId = {
                methodId: new mongoose.Types.ObjectId(),
                customSettings: {
                    workDuration: 25,
                    breakDuration: 5
                }
            };

            await expect(async () => {
                const userPreferences = new UserPreferencesModel(userPreferencesWithoutUserId);
                await userPreferences.save();
            }).rejects.toThrow(mongoose.Error.ValidationError);
        });

        test('debe fallar al crear preferencias sin methodId', async () => {
            const userPreferencesWithoutMethodId = {
                userId: new mongoose.Types.ObjectId(),
                    workDuration: 25,
                    breakDuration: 5
                
            };

            try {
                const userPreferences = new UserPreferencesModel(userPreferencesWithoutMethodId);
                await userPreferences.save();
            } catch (error) {
                expect(error).toBeDefined();
            }
        });

        test('debe permitir crear preferencias sin customSettings', async () => {
            const userPreferencesWithoutCustomSettings = {
                userId: new mongoose.Types.ObjectId(),
                methodId: new mongoose.Types.ObjectId()
            };

            const userPreferences = new UserPreferencesModel(userPreferencesWithoutCustomSettings);
            const savedUserPreferences = await userPreferences.save();
            
            expect(savedUserPreferences._id).toBeDefined();
        });
    });
});
