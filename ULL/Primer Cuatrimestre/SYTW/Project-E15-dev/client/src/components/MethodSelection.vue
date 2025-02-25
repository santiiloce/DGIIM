<template>
  <body>
    <div class="method-selection">
      <h2>Selecciona tu método de estudio</h2>
      <div class="methods">
        <div v-for="method in methods" :key="method.name" class="method-card">
          <h3>{{ method.name }}</h3>
          <p>{{ method.description }}</p>
          <p style="font-weight: bold">
            Tiempo de estudio: <span class="work-duration">{{ method.workDuration }}</span> minutos
          </p>
          <p style="font-weight: bold">
            Tiempo de descanso:
            <span class="break-duration">{{ method.breakDuration }}</span> minutos
          </p>
          <button @click="selectMethod(method)">Seleccionar</button>
        </div>
      </div>
    </div>
  </body>
</template>

<script lang="ts">
import { Types } from 'mongoose'
import { useRouter } from 'vue-router'
import { defineComponent, onMounted, computed } from 'vue'  
import { useAuthStore } from '@/stores/authstore'
import { useUsersStore } from '@/stores/users_store'
import { MethodStudy } from '@/models/methodstudy_model'
import { useMethodsStore } from '@/stores/methods_store'

export default defineComponent({
  name: 'MethodSelection',
  setup() {
    const router = useRouter()
    const authStore = useAuthStore()
    const userStore = useUsersStore()
    const methodsStore = useMethodsStore() 
    const userIDString = authStore.loggedUserId
    const methods = computed(() => methodsStore.methods);

    onMounted(async () => {
      await userStore.getUsers()
      await methodsStore.getMethods() 
    })
    const selectMethod = async (method: MethodStudy) => {
      try {
        if (!userIDString) {
          throw new Error('No se ha encontrado el ID del usuario')
        }
        if (!method._id) {
          throw new Error('No se ha encontrado el ID del método')
        }
        const userID = new Types.ObjectId(userIDString)
        sessionStorage.setItem('userID', userID.toString());
        sessionStorage.setItem('methodID', method._id.toString());
        router.push('/subject')
        
      } catch (error) {
        console.error('Error al seleccionar el método', error)
        alert(error)
      }
    }
    return {
      methods,
      selectMethod,
    }
  },
})
</script>

<style scoped>
.method-selection {
  text-align: center;
  padding: 20px;
}

.methods {
  display: flex;
  width: 100%;
  justify-content: space-around;
  flex-wrap: wrap;
  margin-top: 20px;
  gap: 20px;
}

.method-selection h2 {
  font-size: 2.5rem;
  margin-bottom: 20px;
  color: #12393b;
}

.method-card {
  flex: 1 1 calc(25% - 20px);
  max-width: 300px;
  min-width: 100px;
  border: 1px solid #0a4f58;
  border-radius: 10px;
  box-sizing: border-box;
  padding: 20px;
  box-shadow: 0 4px 20px rgba(255, 255, 255, 0.1);
}

.method-card h3 {
  margin-top: 0;
  color: #2b7288;
  font-weight: bold;
}

.method-card p {
  color: #588157;
}

.method-card button {
  background-color: #344e41;
  color: white;
  border: none;
  padding: 10px 20px;
  border-radius: 20px;
  cursor: pointer;
  transition: background-color 0.4s;
}

.method-card button:hover {
  background-color: #3d9669;
}

.work-duration {
  color: #3d9669;
  font-weight: bold;
  font-size: 1.2em;
}

.break-duration {
  color: #2788a5;
  font-weight: bold;
  font-size: 1.2em;
}
</style>
