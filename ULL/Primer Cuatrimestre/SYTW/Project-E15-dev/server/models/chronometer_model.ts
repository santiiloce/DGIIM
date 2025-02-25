import mongoose, { Schema, Document,Types } from 'mongoose';

interface ChronometerInterface extends Document {
    IDsubject:Types.ObjectId;
    IDuser:Types.ObjectId;
    IDmethod_study:Types.ObjectId
}

const ChronometerSchema:Schema = new Schema({
    IDsubject:{
        type: Schema.Types.ObjectId,
        require: true,
        ref: 'Subject'
    },
    Iduser:{
        type:Schema.Types.ObjectId,
        require: true,
        ref: 'User'
    },
    IDmethod_study:{
        type: Schema.Types.ObjectId,
        require: true,
        ref: 'MethodStudy'
    }
}) 

ChronometerSchema.index({Iduser:1,IDsubject:1},{unique:true})

const Chronometer = mongoose.model<ChronometerInterface>('Chronometer', ChronometerSchema);

export default Chronometer;