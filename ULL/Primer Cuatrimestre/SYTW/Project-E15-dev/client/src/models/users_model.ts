import {Types} from 'mongoose'

export interface UsersInterfaces{
    name:string;
    email:string;
    password: string;
    role:string;
    _id?: Types.ObjectId | string;

    
}

/** class user */
export class User implements UsersInterfaces{
    constructor(
      public name: string,
      public email: string,
      public password: string,
      public role: string,
      public _id?: Types.ObjectId | string
    ) {}
    /** Regular expresion  verific email */
    validateEmail(): boolean { return /^[\w-.]+@([\w-]+\.)+[\w-]{2,4}$/.test(this.email); }  
}