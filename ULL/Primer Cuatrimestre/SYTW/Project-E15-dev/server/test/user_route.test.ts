const request = require('supertest')
import {app,servers} from './../server'
import mongoose from 'mongoose'
import User from './../models/user_model'

let server:any;


describe('Probando la api rest de users',() =>{
  afterAll(async ()=>{
    await mongoose.connection.close(true);
    await mongoose.disconnect();
    servers.close();
  })
  afterEach(async () =>{
    await User.deleteMany({});
    jest.clearAllMocks();
  })
  beforeAll(async () =>{
    await mongoose.disconnect();
    await mongoose.connect('mongodb://localhost:27017/testdb');
  })
  test('test GET users' ,async() =>{
    const response = await request(app).get('/user/')
     expect(response.status).toBe(200)
  })

  test('test POST user', async () =>{
    const response = await request(app)
      .post('/user/register')
      .send({ name: 'John Doe', email: 'john@example.com',password: "jhon",role:"student" });
    expect(response.status).toBe(201);
  })
  test('test POST user error 500', async () =>{
    const response = await request(app)
      .post('/user/register')
      .send({ name: 'Johdsfn Doe', email: 'jofsdhn@example.com',password: "jhon",role:"studegnt" });
    expect(response.status).toBe(500);
  })
  test('test POST user error 500', async () =>{
    const response = await request(app)
      .post('/user/register')
      .send({ name: 'Johdsfn Doe', email: 'jofsdhn@example.com',password: "jhon",role:"studegnt" });
    expect(response.status).toBe(500);
  })
  test('test POST user error 400', async () =>{
     await request(app)
      .post('/user/register')
      .send({ name: 'Johdsfn Doe', email: 'jofsdhn@example.com',password: "jhon",role:"student" });
    const response = await request(app)
      .post('/user/register')
      .send({ name: 'Johdsfn Doe', email: 'jofsdhn@example.com',password: "jhon",role:"student" });
    expect(response.status).toBe(400);
  })
  test('test POST login sucesfull', async () =>{
     await request(app)
      .post('/user/register')
      .send({ name: 'John Doe', email: 'jofn@example.com',password: "jhon",role:"student" });
      const response = await request(app)
      .post('/user/login')
      .send({ email: 'jofn@example.com', password: "jhon"});
      expect(response.status).toBe(200);    
  })
  test('test POST login error 404', async () =>{
    await request(app)
     .post('/user/register')
     .send({ name: 'John Doe', email: 'jofn@example.com',password: "jhon",role:"student" });
     const response = await request(app)
     .post('/user/login')
     .send({ email: 'jofn@example.com'});
     expect(response.status).toBe(400);    
 })   
 test('test POST login error 400', async () =>{
  await request(app)
   .post('/user/register')
   .send({ name: 'John Doe', email: 'jofn@example.com',password: "jhon",role:"student" });
   const response = await request(app)
   .post('/user/login')
   .send({ email: 'jodffgdfn@example.com', password: 'fdsd'});
   expect(response.status).toBe(404);    
}) 
test('test POST login error 401', async () =>{
  await request(app)
   .post('/user/register')
   .send({ name: 'John Doe', email: 'jofn@example.com',password: "jhon",role:"student" });
   const response = await request(app)
   .post('/user/login')
   .send({ email: 'jofn@example.com', password: 'fdsd'});
   expect(response.status).toBe(401);    
}) 

test('test PUT user sucessfull', async () =>{
  const usuario = await User.create({ name: 'Juan', email: 'juan@test.com',password: "juan",role:"student"});
   const response = await request(app)
   .put('/user/' + usuario._id)
   .send({ email: 'jofn@example.com', password: 'fdsd'});
   expect(response.status).toBe(201);    
})

test('test PUT user error 500', async () =>{
   const response = await request(app)
   .put('/user/fdggfdsgdf')
   .send({ email: 'jofn@example.com', password: 'fdsd'});
   expect(response.status).toBe(500);    
})

test('test DELETE user sucessfull', async () =>{
  const usuario = await User.create({ name: 'Juan', email: 'juan@test.com',password: "juan",role:"student"});
   const response = await request(app)
   .delete('/user/' + usuario._id);
   expect(response.status).toBe(200);    
})

test('test DELETE user error 500', async () =>{
   const response = await request(app)
   .delete('/user/dakfhaih');
   expect(response.status).toBe(500);    
})
})
