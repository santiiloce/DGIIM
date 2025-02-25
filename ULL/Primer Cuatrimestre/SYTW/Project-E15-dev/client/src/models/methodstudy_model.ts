import {Types} from 'mongoose'

export interface MethodStudyInterfaces  {
    name:string;
    description:string;
    workDuration:number;
    breakDuration:number;
    _id?:Types.ObjectId;
}

export class MethodStudy implements MethodStudyInterfaces{
    constructor(
      public name:string,
      public description:string,
      public workDuration:number,
      public breakDuration:number,
      public _id?:Types.ObjectId
  ) {}
}
