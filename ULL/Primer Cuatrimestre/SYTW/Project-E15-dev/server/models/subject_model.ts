import mongoose, { Schema, Document } from 'mongoose';
import { Types } from 'mongoose';

interface SubjectInterface extends Document {
    name: string;
    //type_education: string;
    description:string;
    _id:Types.ObjectId;
}

const SubjectSchema:Schema = new Schema({
    name:{
        type:String,
        required: [true, 'The name of the subject is required.'],
        minlength: [3, 'The minimum length is 3 characters'],
        maxlength: [20, 'The maximum length is 20 characters'],        
    },
    description:{
        type:String,
        required: [false, 'Description is required.'],
        default:'no description'
    },
    _id:{
        type:Schema.Types.ObjectId,
        required:true,
        default:()=>new Types.ObjectId()
    }
})

const Subject = mongoose.model<SubjectInterface>('Subject', SubjectSchema);
export default Subject;