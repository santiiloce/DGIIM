import { ref } from 'vue'
import { defineStore } from 'pinia'
import type {HistorySubjectInterface } from '@/models/history_study_model'
import { HistorySubject } from '@/models/history_study_model'
import { Types } from 'mongoose';
import dotenv from 'dotenv';

dotenv.config();
export const useHistorySubjectStorre = defineStore('HistorySubject',()=>{
    const historysubject = ref<HistorySubjectInterface []>([]);

    async function getHistorySubject () {
        let port:number | string= process.env.PORT || 5300; 
        const response = await fetch('http://localhost:'+ port)
        const data = await response.json();
        historysubject .value= data.map((historysubject_now:any)=> new HistorySubject(historysubject_now.IDsubject,historysubject_now.IDuser,historysubject_now.date,historysubject_now.time,historysubject_now._id))
    }
    async function addHistorySubject (historysubjectadd:HistorySubjectInterface) {
        historysubject .value.push(historysubjectadd)
    }
    async function deleteHistorySubject(id: Types.ObjectId) 
    { 
        const index = historysubject.value.findIndex(historysubject_now => {if(historysubject_now._id)historysubject_now._id.equals(id)}); 
        if (index !== -1) 
        { 
            historysubject.value.splice(index, 1); 
        } 
        else 
        { 
           console.error("History Study no found"); 
        } 
    }
    function putHistorySubject(id: Types.ObjectId, datosActualizados: Partial<HistorySubjectInterface>) 
      { 
        const index = historysubject.value.findIndex(historysubject_now => historysubject_now._id?.equals(id)); 
         if (index !== -1) 
         {  
            historysubject.value[index] = { ...historysubject.value[index], ...datosActualizados }; } 
         else 
         { 
           console.error("History Study no found"); 
         } 
    }
    return {historysubject ,addHistorySubject ,getHistorySubject ,putHistorySubject ,deleteHistorySubject }
})