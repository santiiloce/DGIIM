import { ref, computed } from 'vue'
import { defineStore } from 'pinia'

export const useTimerStore = defineStore('Timer', () => {
    const currentTime = ref<number>(0);
    const isBreak = ref<boolean>(false);
    const isRunning = ref<boolean>(false);
    const intervalId = ref<number | null>(null);

    const timeDisplay = computed(() => {
        const minutes = Math.floor(currentTime.value / 60);
        const seconds = currentTime.value % 60;
        return `${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;
    });

    function startTimer(workDuration: number, breakDuration: number) {
        if (isRunning.value) return;
        
        if (currentTime.value === 0) {
            currentTime.value = workDuration * 60;
            isBreak.value = false;
        }

        isRunning.value = true;

        intervalId.value = window.setInterval(() => {
            if (currentTime.value > 0) {
                currentTime.value--;
            } else {
                if (!isBreak.value) {
                    isBreak.value = true;
                    currentTime.value = breakDuration * 60;
                } else {
                    stopTimer();
                }
            }
        }, 1000);
    }

    function stopTimer() {
        if (intervalId.value) {
            clearInterval(intervalId.value);
            intervalId.value = null;
        }
        isRunning.value = false;
        currentTime.value = 0;
        isBreak.value = false;
    }

    function pauseTimer() {
        if (intervalId.value) {
            clearInterval(intervalId.value);
            intervalId.value = null;
        }
        isRunning.value = false;
    }

    function resetTimer() {
        stopTimer();
        currentTime.value = 0;
        isBreak.value = false;
        isRunning.value = false;
    }
    

    return {
        currentTime,
        isBreak,
        isRunning,
        timeDisplay,
        startTimer,
        stopTimer,
        pauseTimer,
        resetTimer
    };
})
