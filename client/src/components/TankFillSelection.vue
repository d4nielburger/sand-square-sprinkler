<template>
    <div>
      <h3>Tank Fill Selection</h3>
      <button class="control-btn" @click="selectSmall">small</button>
      <button class="control-btn" @click="selectLarge">large</button>
      <button class="control-btn" @click="selectNone">drain</button>
    </div>
  </template>
  
  <script>
  const API_URI = 'http://localhost:3000/sss/api';
  
  export default {
    methods: {
      async selectSmall() {
        try {
          await fetch(`${API_URI}/control/tank`, {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({ select: 'small' }),
          });
        } catch (error) {
          console.error('Error:', error);
        }
      },
      async selectLarge() {
        try {
          await fetch(`${API_URI}/control/tank`, {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({ select: 'large' }),
          });
        } catch (error) {
          console.error('Error:', error);
        }
      },
      async selectNone() {
        try {
          await fetch(`${API_URI}/control/tank`, {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({ select: 'none' }),
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
  