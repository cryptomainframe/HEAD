define(['application', 'backbone', 'lib/api'], function (App, Backbone, api) {
    return Backbone.Model.extend({
        call: function () {
            var self = this;

            switch (this.get('name')) {
                case 'gesture':
                    api.setGesture(this.get('gesture'), 1, this.get('speed'), this.get('magnitude'));
                    break;
                case 'emotion':
                    api.setEmotion(this.get('emotion'), this.get('magnitude'), parseFloat(this.get('duration')));
                    break;
                case 'look_at':
                    api.setFaceTarget(this.get('x'), this.get('y'), this.get('z'));
                    break;
                case 'gaze_at':
                    api.setGazeTarget(this.get('x'), this.get('y'), this.get('z'));
                    break;
                case 'speech':
                    api.robotSpeech(this.get('text'), this.get('lang'));
                    break;
                case 'interaction':
                    api.enableInteractionMode();
                    break;
                case 'pause':
                    this.trigger('pause');
                    break;
                case 'expression':
                    api.blenderMode.disableFace();
                    // Wait for blender to disable faces
                    setTimeout(function () {
                        api.setExpression(self.get('expression'), self.get('magnitude'));
                    }, 50);
                    break;
            }
        },
        finish: function () {
            switch (this.get('name')) {
                case 'interaction':
                    api.disableInteractionMode();
                    break;
                case 'expression':
                    api.setExpression(this.get('expression'), 0.01);
                    setTimeout(api.blenderMode.enable, 1000);
                    break;
            }
        },
        toJSON: function () {
            var json = Backbone.Model.prototype.toJSON.call(this);
            if (this.get('el')) delete json['el'];

            return json;
        },
        destroy: function () {
            // remove an associated element
            if (this.get('el'))
                $(this.get('el')).remove();

            Backbone.Model.prototype.destroy.call(this);
        }
    });
});