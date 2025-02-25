import { Types } from "mongoose";

export interface HistorySubjectInterface {
    _id?:Types.ObjectId;
    IDsubject:Types.ObjectId;
    IDuser:Types.ObjectId;
    date:Date;
    time:Number;
}

export class HistorySubject implements HistorySubjectInterface{
    constructor(
        public IDsubject:Types.ObjectId,
        public IDuser:Types.ObjectId,
        public date:Date,
        public time:Number,
        public _id?:Types.ObjectId
      ) {}    
}