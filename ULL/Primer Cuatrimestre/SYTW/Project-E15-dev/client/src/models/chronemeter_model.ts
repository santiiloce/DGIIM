import { Types } from "mongoose";

export interface ChronometerInterfaces {
    IDsubject:Types.ObjectId;
    IDuser:Types.ObjectId;
    IDmethod_study:Types.ObjectId;
    _id?:Types.ObjectId;
}

export class Chronometer{
    constructor(
        public IDsubject:Types.ObjectId,
        public IDuser:Types.ObjectId,
        public IDmethod_study:Types.ObjectId,
        public _id?:Types.ObjectId
      ) {}      
}