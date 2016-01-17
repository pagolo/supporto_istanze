<?php
class supporto_istanze_motivazioni_views_handler_field extends views_handler_field {
  function abbrevia_testo($text) {
    $ret = strip_tags(substr($text, 0, 8) . (strlen($text) > 8 ? '...(segue)' : ''));
    return $ret;
  }
  function render($values) {
    static $count = 1;
    $value = check_plain($this->get_value($values));
    if (empty($value)) {
      $html = '---';
    } else {
      $value = str_replace("\r\n",'<br />', $value);
      $value = str_replace("\r",'<br />', $value);
      $value = str_replace("\n",'<br />', $value);
      $full = str_replace(array('\'', '"'),'&#39;',$value);
      $abbr = $this->abbrevia_testo($value);
      $abbr = str_replace(array('\'', '"'),'&#39;',$abbr);
      $html = '<div id=\'mot_' . $count . '\' style="display:none" onmouseover=\'this.innerHTML="' . $full . '"\' onmouseout=\'this.innerHTML="' . $abbr . '"\' class=\'motivazioni\'>' . $value . '</div>';
      $html .= "<script type=\"text/javascript\">\n//<![CDATA[\nvar div=document.getElementById('mot_".$count."');\ndiv.innerHTML=\"" . $abbr . "\";\ndiv.style.display='block';\n//]]>\n</script>";
    }
    ++$count;
    return $html;
  }
}
