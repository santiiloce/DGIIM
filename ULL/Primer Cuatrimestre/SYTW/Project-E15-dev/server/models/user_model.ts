import mongoose, { Schema, Document } from 'mongoose';

interface UserInterface extends Document {
    name: string;
    email: string;
    password: string;
    role: string;
}

const UserSchema: Schema = new Schema({
    name: {
        type: String,
        required: [true, 'The name of the user is required.'],
        minlength: [3, 'The minimum length is 3 characters'],
        maxlength: [20, 'The maximum length is 20 characters'],
    },
    email: {
        type: String,
        required: [true, 'The email is required.'],
        unique: true,
        match: [ /^\w+([.-]?\w+)*@\w+([.-]?\w+)*(\.\w{2,3})+$/,
            'El correo electrónico no es válido'],
    },
    password: {
        type: String,
        required: [true, 'The password is required.']
    },
    role: {
        type: String,
        enum: ['student', 'college', 'teacher', 'master'],
        default: 'student'
    }
});

const User = mongoose.model<UserInterface>('User', UserSchema);
export default User;