  (function ($) {
     // override the default confirmation dialog behavior
     Drupal.behaviors.confirm = { 

      // Get the jQuery events.
      attach: function(context, settings) {
      var events =  $('.cancelButtonClass').clone(true).data('events'); 

      $('.cancelButtonClass').unbind('mousedown'); // Remove the mousedown event.

      $('.cancelButtonClass').mousedown(function () { 
           // Popup the confirmation
           if (confirm('Are you sure you want to delete the Group?')) {
             // if YES, then we fire the AJAX event 
             $('.cancelButtonClass').trigger('cancelInstanceEvent'); 
           }
           // Override the default action.
           return false;
        });
    }
            }
  })(jQuery);
 
 
