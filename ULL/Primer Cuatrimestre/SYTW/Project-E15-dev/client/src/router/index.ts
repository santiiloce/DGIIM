import HomeView from '../views/HomeView.vue'
import TimerView from '@/views/TimerView.vue'
import Loginview from '@/views/LoginView.vue'
import UserList from '@/components/UserList.vue'
import RegisterUser from '@/views/RegisterView.vue'
import MethodSelectView from '@/views/MethodSelectView.vue'
import SubjectCreatorView from '@/views/SubjectCreatorView.vue'
import { createRouter, createWebHistory } from 'vue-router'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: HomeView,
    },
    {
      path: '/about',
      name: 'about',
      component: () => import('../views/AboutView.vue'),
    },
    {
      path: '/users',
      name:'UserList',
      component: UserList,
    },
    { 
      path: '/register', 
      name: 'Register', 
      component: RegisterUser, 
    },
    {
      path: '/login',
      name: 'UserLogin',
      component: Loginview
    },
    {
      path: '/timer',
      name: 'TimerView',
      component: TimerView
    },
    {
      path: '/method-selection',
      name: 'MethodSelection',
      component: MethodSelectView
    },
    {
      path: '/subject',
      name: 'SubjectCreator',
      component: SubjectCreatorView
    }
  ],
})

export default router
