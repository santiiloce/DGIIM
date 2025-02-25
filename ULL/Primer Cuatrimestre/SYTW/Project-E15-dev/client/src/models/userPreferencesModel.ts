import { Types } from 'mongoose'

export interface UserPreferencesInterface {
    userId: Types.ObjectId
    methodId: Types.ObjectId
    subjectId: Types.ObjectId
    workDuration: number
    breakDuration: number
    createdAt: Date
    updatedAt: Date
    _id?: Types.ObjectId
}

export class UserPreferences implements UserPreferencesInterface {
    constructor(
        public userId: Types.ObjectId,
        public methodId: Types.ObjectId,
        public subjectId: Types.ObjectId,
        public workDuration: number,
        public breakDuration: number,
        public createdAt: Date = new Date(),
        public updatedAt: Date = new Date(),
        public _id?: Types.ObjectId,
    ) {}
}
