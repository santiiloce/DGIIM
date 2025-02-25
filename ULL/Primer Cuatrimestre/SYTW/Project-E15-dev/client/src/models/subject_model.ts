import {Types} from 'mongoose'

export interface SubjectInterfaces  {
    _id?:Types.ObjectId;
    name: string;
    description:string;
}

/** class Subject */
export class Subject implements SubjectInterfaces{
    constructor(
      public name:string,
      public description:string,
      public _id?:Types.ObjectId
    ) {}
}