import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-main',
  templateUrl: './main.component.html',
  styleUrls: ['../baseStyle.css', './main.component.css']
})
export class MainComponent implements OnInit {

  constructor(private router: Router) { }

  ngOnInit() {
  }

  RedirectProjector() {
    this.router.navigate(['/projector']);
  }

  RedirectAudioSwitch() {
    this.router.navigate(['/audio-switch']);
  }

  RedirectChrismasTree() {
    this.router.navigate(['/christmas-tree']);
  }
}
