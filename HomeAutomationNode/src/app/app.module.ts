import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { RouterModule, Routes } from '@angular/router';

import { AppComponent } from './app.component';
import { MainComponent } from './main/main.component';
import { ProjectorComponent } from './projector/projector.component';
import { AudioSwitchComponent } from './audio-switch/audio-switch.component';
import { HomeButtonComponent } from './home-button/home-button.component';
import { ChristmasTreeComponent } from './christmas-tree/christmas-tree.component';

import { HttpClientModule } from '@angular/common/http';
import { HTTPAPIService } from './httpapi.service';
import {ConstantesService} from './constantes.service';

const appRoutes: Routes = [
  { path: '', component: MainComponent },
  { path: 'main', component: MainComponent },
  { path: 'projector', component: ProjectorComponent },
  { path: 'audio-switch', component: AudioSwitchComponent },
  { path: 'christmas-tree', component: ChristmasTreeComponent }
  ];

@NgModule({
  declarations: [
    AppComponent,
    MainComponent,
    ProjectorComponent,
    AudioSwitchComponent,
    HomeButtonComponent,
    ChristmasTreeComponent
  ],
  imports: [
    RouterModule.forRoot(
      appRoutes,
      { enableTracing: true } // <-- debugging purposes only
    ),
    BrowserModule,
    HttpClientModule
  ],
  providers: [
    HTTPAPIService,
    ConstantesService
  ],
  bootstrap: [
    AppComponent,
    MainComponent,
    ProjectorComponent
  ]
})
export class AppModule { }
