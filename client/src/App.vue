<script setup>
import GaragePumpControl from './components/GaragePumpControl.vue';
import TankFillSelection from './components/TankFillSelection.vue';
import SprinklerControl from './components/SprinklerControl.vue';
import HoseControl from './components/HoseControl.vue';
</script>

<template>
  <div id="app">
    <div id="control" class="main-element">
      <h2 style="text-align: center; font-size: 40px; font-weight: bold;">Controls</h2>
      <br>
      <br>
      <GaragePumpControl/>
      <br>
      <TankFillSelection/>
      <br>
      <SprinklerControl/>
      <br>
      <HoseControl/>
    </div>
  </div>
</template>

<style scoped>
.main-element{
  padding: 2em;
}
</style>