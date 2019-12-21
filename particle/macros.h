#ifndef forParticlesInSystem

#define forParticlesInSystem(endId, particleData, systemID) for(int i = 0; i < endId; i++) {\
    if (particleData->particles[i].systemID != systemID)\
        continue;\

#define endForParticlesInSystem }

#endif