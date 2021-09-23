import bcrypt from 'bcryptjs'

const users = [
  {
    name: 'Admin User',
    email: 'admin@example.com',
    password: bcrypt.hashSync('123456', 10),
    isAdmin: true,
  },
  {
    name: 'Jay_ganesh',
    email: 'jayganesh@example.com',
    password: bcrypt.hashSync('ganesh@3479', 10),
  },
  {
    name: 'Jay_ganesh_19355',
    email: 'jayganesh19355@example.com',
    password: bcrypt.hashSync('ganesh@3479', 10),
  },
  {
    name: 'Jay',
    email: 'ganeshvengala@example.com',
    password: bcrypt.hashSync('123456', 10),
  },
  {
    name: 'test',
    email: 'test@example.com',
    password: bcrypt.hashSync('123456', 10),
  },
  {
    name: 'test1',
    email: 'test1@example.com',
    password: bcrypt.hashSync('123456', 10),
  },
  {
    name: 'test2',
    email: 'test2@example.com',
    password: bcrypt.hashSync('123456', 10),
  },
]

export default users
