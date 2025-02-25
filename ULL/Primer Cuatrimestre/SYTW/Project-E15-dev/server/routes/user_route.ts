import { Request, Response } from "express";
import User from '../models/user_model';
import jwt from 'jsonwebtoken'
import bcrypt from 'bcrypt';
const express = require("express");
const router = express.Router();


router.get("/", async (req: Request, res: Response) => {
  try{
    const user = await User.find();
    res.status(200).json(user);
  } catch (error: unknown) {
    if (error instanceof Error) {
      console.error('Error:', error.message);
      res.status(500).json({ error: 'Internal Server Error' });
    }
  }
});

router.post("/register", async (req: Request, res: Response) => {
  try {
    const { email, password, name, role } = req.body;
    // const { email } = req.body;
    const userExists = await User.findOne({ email });
    if (userExists) {
      return res.status(400).json({ message: 'Email alrady registered' });
    }
    const saltRounds = 10; 
    const hashedPassword = await bcrypt.hash(password, saltRounds);

    const new_user = new User({
      email,
      password: hashedPassword,
      name,
      role,
    });
    console.log(new_user.password);
    await new_user.save();
    res.status(201).json({
      message: "User created successfully"
  });
  } catch (error: unknown) {
    if (error instanceof Error) {
      console.error('Error:', error.message);
      res.status(500).json({ error: error.message });
    } else {
      res.status(500).json({ error: 'Internal Server Error' });
    }
  }
});

router.post("/login", async (req: Request, res: Response) => {
  try {
    const SECRET_KEY=process.env.SECRET_KEY || 'default_token';
    const TOKEN_EXPIRATION = process.env.TOKEN_EXPIRATION || '1h'
    const { email,password } = req.body;
    if(!email || !password || email === "" || password === "") 
      return res.status(400).json({message: 'User or password must to be proved'})
    const reqUser = await User.findOne({ email });
    if (!reqUser) {
      return res.status(404).json({ message: 'User not found' });
    }

    const isPasswordValid = await bcrypt.compare(password, reqUser.password);
    if (!isPasswordValid) {
      return res.status(401).json({ message: 'Invalid password' });
    }

      const json = jwt.sign({email},SECRET_KEY,{ expiresIn: TOKEN_EXPIRATION})
      res.status(200).json({token: json,email: reqUser?.email,name: reqUser?.name, userID: reqUser?._id });

  } catch (error: unknown) {
    if (error instanceof Error) {
      console.error('Error:', error.message);
      res.status(500).json({ error: 'Internal Server Error' });
    }
  }
});

router.put("/:id", async (req: Request, res: Response) => {
  try {
    await User.findByIdAndUpdate(req.params.id, req.body);
    res.status(201).json({
      message: "User updated successfully",
    });
  } catch (error: unknown) {
    if (error instanceof Error){
      console.error('Error:', error.message);
      res.status(500).json({ error: 'Internal Server Error' });
    }
  }
});

router.delete("/:id", async (req: Request, res: Response) => {
  try {
    await User.findByIdAndDelete(req.params.id);
    res.status(200).json({
      message: "User deleted successfully",
    });
  } catch (error: unknown) {
    if (error instanceof Error){
      console.error('Error:', error.message);
      res.status(500).json({ error: 'Internal Server Error' });
    }
  }
});


module.exports = router;
