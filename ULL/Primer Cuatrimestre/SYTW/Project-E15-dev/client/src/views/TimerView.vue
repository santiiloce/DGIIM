<script setup lang="ts">
import NavbarMenu from "@/components/NavbarMenu.vue"
</script>
<template>
    <main>
        <NavbarMenu />
        <div>
            <TimerComponent />
        </div>
    </main>
    
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import TimerComponent from '@/components/TimerComponent.vue'

export default defineComponent({
    name: 'TimerView',
    components: {
        TimerComponent
    }
})
</script>
