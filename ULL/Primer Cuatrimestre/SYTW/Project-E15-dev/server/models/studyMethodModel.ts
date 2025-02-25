import mongoose, { Schema, Document } from "mongoose";

interface StudyMethodInterface extends Document {
    name: string;
    description: string;
    workDuration: number;
    breakDuration: number;
}

const StudyMethodSchema = new Schema({
    name: {
        type: String,
        required: true,
    },
    description: {
        type: String,
        required: true,
    },
    workDuration:{
        type: Number,
        required: true,
    },
    breakDuration:{
        type: Number,
        required: true,
    }
    });

    const StudyMethodModel = mongoose.model<StudyMethodInterface>(
    "StudyMethodModel",
    StudyMethodSchema
);
export default StudyMethodModel;
