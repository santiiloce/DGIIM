import mongoose, { Schema, Document,Types } from 'mongoose';

interface HistoryInterface extends Document {
    userId:string;
    methodId:string;
    subjectId:string;
    workDuration:number;
    breakDuration:number;
    date:Date;
}


const HistorySchema:Schema = new Schema({
    userId:{
        type: Schema.Types.ObjectId,
        required:true,
        ref:'User'
    },
    methodId:{
        type: Schema.Types.ObjectId,
        required:true,
        ref:'Method'
    },
    subjectId:{
        type: Schema.Types.ObjectId,
        required:true,
        ref:'StudyMethodModel'
    },
    workDuration:{
        type:Number,
        required:true
    },
    breakDuration:{
        type:Number,
        required:true
    },
    date:{
        type:Date,
        default:Date.now
    }
},{ timestamps: true });

HistorySchema.index({date:1,userId:1,methodId:1,subjectId:1},{unique:true})

const History = mongoose.model<HistoryInterface>('History', HistorySchema);

export default History;