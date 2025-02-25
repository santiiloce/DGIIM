import { ref } from 'vue'
import { defineStore } from 'pinia'
import type {ChronometerInterfaces } from '@/models/chronemeter_model'
import { Chronometer } from '@/models/chronemeter_model'
import { Types } from 'mongoose';
import dotenv from 'dotenv';

dotenv.config();
export const useHistorySubjectStorre = defineStore('HistorySubject',()=>{
    const Chronometers = ref<ChronometerInterfaces []>([]);

    async function getChronometer () {
        let port:number | string= process.env.PORT || 5300; 
        const response = await fetch('http://localhost:'+ port)
        const data = await response.json();
        Chronometers .value= data.map((chronometer:any)=> new Chronometer(chronometer.IDsubject,chronometer.IDuser,chronometer.IDmethod_study,chronometer._id))
    }
    async function addChronometer (Chronometersadd:ChronometerInterfaces) {
        Chronometers .value.push(Chronometersadd)
    }
    async function deleteChronometer(id: Types.ObjectId) 
    { 
        const index = Chronometers.value.findIndex(chronometer=> {if(chronometer._id)chronometer._id.equals(id)}); 
        if (index !== -1) 
        { 
            Chronometers.value.splice(index, 1); 
        } 
        else 
        { 
           console.error("Chronometer no found"); 
        } 
    }
    function putChronometer(id: Types.ObjectId, datosActualizados: Partial<ChronometerInterfaces>) 
      { 
        const index = Chronometers.value.findIndex(chronometer => chronometer._id?.equals(id)); 
         if (index !== -1) 
         {  
            Chronometers.value[index] = { ...Chronometers.value[index], ...datosActualizados }; } 
         else 
         { 
           console.error("Chronometer no found"); 
         } 
    }
    return {Chronometers ,addChronometer ,getChronometer ,putChronometer ,deleteChronometer}
})