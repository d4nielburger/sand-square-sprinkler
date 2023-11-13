<template>
  <div>
    <h3>Garage Pump Control</h3>
    <button @click="pumpOn">Pump On</button>
    <button @click="pumpOff">Pump Off</button>
  </div>
</template>

<script>
const API_URI = 'http://localhost:3000/sss/api';

export default {
  methods: {
    async pumpOn() {
      try {
        await fetch(`${API_URI}/control/garage-pump`, {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ state: 'ON' }),
        });
      } catch (error) {
        console.error('Error:', error);
      }
    },
    async pumpOff() {
      try {
        await fetch(`${API_URI}/control/garage-pump`, {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ state: 'OFF' }),
        });
      } catch (error) {
        console.error('Error:', error);
      }
    },
  },
};
</script>

<style scoped>
/* Your CSS here */
</style>
