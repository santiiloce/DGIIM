<template>
    <div class="timer-component">
        <h2 class="timer-title">Study Time</h2>
        <div class="timer-visual">
            <p class="timer-display">{{ timeDisplay }}</p>
        </div>
        <div class="button-collections">
            <button class="timer-button-start" @click="startTimer(workDuration, breakDuration)">START</button>
            <button class="timer-button-pause" @click="pauseTimer">PAUSE</button>
            <button class="timer-button-stop" @click="stopTimer">RESTART</button>
        </div>
    </div>
</template>

<script lang="ts">
import { useAuthStore } from '@/stores/authstore'
import { useTimerStore } from '@/stores/timer_store'
import { defineComponent, onMounted, computed, ref } from 'vue'
import { usePreferencesStore } from '@/stores/userPreferences_store'


import { Types } from 'mongoose'
export default defineComponent({
    name: 'TimerComponent',
    setup() {
        const authStore = useAuthStore();
        const timerStore = useTimerStore();
        const userIDString = authStore.loggedUserId
        const preferencesStore = usePreferencesStore();
        if (!userIDString) {
            throw new Error('No se ha encontrado el ID del usuario')
        }
        const userID = new Types.ObjectId(userIDString)
        const timeDisplay = computed(() => timerStore.timeDisplay)
        const workDuration = ref(0);
        const breakDuration = ref(0);
        const methodName = ref('');
        onMounted(async () => {
            try {
                const preferences = await preferencesStore.getUserPreferences(userID);
                console.log("preferences", preferences)
                if (preferencesStore.userPreferences.length > 0) {
                    const preferences = preferencesStore.userPreferences[0];
                    workDuration.value = preferences.workDuration;
                    breakDuration.value = preferences.breakDuration;
                }

            } catch (error) {
                console.error('Error al obtener las preferencias del usuario:', error);
            }
        });
        const startTimer = (workDuration: number, breakDuration: number) => {
            timerStore.startTimer(workDuration, breakDuration)
        }
        const pauseTimer = () => {
            timerStore.pauseTimer()
        }

        const stopTimer = () => {
            timerStore.stopTimer()
        }

        return {
            timeDisplay,
            startTimer,
            workDuration,
            breakDuration,
            pauseTimer,
            stopTimer,
            methodName
        }
    } 
})
</script>

<style scoped>

body {
    background-color: #151B23;
    margin: 0;
    width: 100vw;
    height: 100vh;
    display:grid;
    place-items: center;
    overflow: hidden;
}

.timer-component {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
}

.timer-component h2{
    margin-bottom: 50px;
    font-size: 4rem;
}

.timer-visual {
    display: flex;  
    align-items: center;
    justify-content: center;
    width: 350px;
    height: 350px;
    border: 6px solid rgb(18, 102, 102);
    color: rgb(18, 102, 102);
    border-radius: 50%;
    font-family: monospace;
    font-size: 4rem;
}

.timer-title {
    font-family:Verdana, Geneva, Tahoma, sans-serif ;
    font-size: 2rem;
}

.button-collections {
    margin-top: 50px;
    display: flex;
    justify-content: center;
}

.button-collections button {
    width: 120px;
    height: 50px;
    margin: 0 10px;
    padding: 10px 20px;
    font-size: 1rem;
    background-color: #4c7761;
    color: white;
    border: none;
    cursor: pointer;
    transition: background-color 0.3s, transform 0.3s;
    border-radius: 25px;
}

.button-collections button:hover {
    background-color: #3d9669;
    transform: scale(1.05);
    cursor: pointer;
}

</style>

